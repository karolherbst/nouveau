/*
 * Copyright 2012 Red Hat Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs
 */

#include <curses.h>
#include <signal.h>
#include <ctype.h>
#include <menu.h>
#include <form.h>

#include <nvif/client.h>
#include <nvif/device.h>
#include <nvif/class.h>
#include <nvif/ioctl.h>

#include <sys/time.h>

#include "util.h"

static struct nvif_client client;
static struct nvif_device _device, *device = &_device;
static struct nvif_object perfmon;
static int nr_signals; /* number of signals for all domains */

#define SEC_US  1000000
#define REFRESH_PERIOD SEC_US

/*******************************************************************************
 *
 ******************************************************************************/

enum ui_colour {
	UI_DEFAULT = 0,
	UI_BLACK_GREEN
};

struct ui_window {
	WINDOW *win;
	enum ui_colour colour;
	const char *status;
	int  (*create)(struct ui_window *, int c, int r);
	void (*destroy)(struct ui_window *);
	void (*redraw)(struct ui_window *);
	bool (*driver)(struct ui_window *, int k);
};

/*******************************************************************************
 *
 ******************************************************************************/

struct ui_table {
	struct ui_window w;
	FIELD **data;
	FORM   *form;
	int y, r, c;
	char *(*layout)(struct ui_table *);
	void  (*change)(struct ui_table *, FIELD *, int x, int y);
	void  (*action)(struct ui_table *, FIELD *, int x, int y);
	void  (*redraw)(struct ui_table *);
	bool  (*driver)(struct ui_table *, int k);
};

static void
ui_field_change(FORM *f)
{
	struct ui_table *t = form_userptr(f);
	if (t->change) {
		FIELD *f = current_field(t->form);
		int i = field_index(f);
		int y = i / t->c;
		int x = i % t->c;
		t->change(t, f, x, y);
	}
}

static void
ui_table_destroy(struct ui_window *w)
{
	struct ui_table *t = (void *)w;
	int i = -1;

	unpost_form(t->form);
	free_form(t->form);

	while (t->data[++i])
		free_field(t->data[i]);
	free(t->data);
}

static int
ui_table_create(struct ui_window *win, int c, int r)
{
	struct ui_table *t = (void *)win;
	char *layout = t->layout(t);
	int f = layout[0];
	int s = layout[1];
	int l = layout[2];
	int x, y, n, p;
	FIELD **v;

	if (s) {
		n  = c - (f + 1) - 1;
		n /= (s + 1) + l;
		l *= n;
	} else {
		l = max(l, c - (f + 1));
		n = 0;
	}

	t->c = 2 + n;
	t->r = r;

	t->data = malloc(sizeof(*t->data) * ((t->c * t->r) + 1));
	for (y = 0; y < t->r; y++) {
		t->data[(y * t->c) + 0] = new_field(1, f, y, 0, 0, 0);
		for (x = 1, p = (f + 1); x < n + 1; x++, p += (s + 1))
			t->data[(y * t->c) + x] = new_field(1, s, y, p, 0, 0);
		t->data[(y * t->c) + x] = new_field(1, l, y, p, 0, 0);
	}
	t->data[y * t->c] = NULL;

	v = t->data - 1;
	while (*(++v))
		field_opts_off(*v, O_ACTIVE);

	t->form = new_form(t->data);
	set_form_sub(t->form, win->win);
	set_form_userptr(t->form, t);
	set_field_term(t->form, ui_field_change);
	post_form(t->form);
	return 0;
}

static void
ui_table_redraw(struct ui_window *w)
{
	struct ui_table *t = (void *)w;
	t->redraw(t);
}

static bool
ui_table_driver(struct ui_window *w, int k)
{
	struct ui_table *t = (void *)w;
	FIELD *v = current_field(t->form);
	int i = field_index(v);
	int y = i / t->c;
	int x = i % t->c;

	switch (k) {
	case ' ':
		t->y = 0;
		return true;
	case KEY_UP:
// XXX: buggy until we move the initial cursor to the correct location
		if (y == 2) {
			if (t->y > 0)
				t->y--;
			return true;
		}
		form_driver(t->form, REQ_UP_FIELD);
		break;
	case KEY_PPAGE:
		t->y -= (t->r - 2);
		if (t->y < 0)
			t->y = 0;
		return true;
	case KEY_HOME:
// TODO: move cursor to top entry
		t->y = 0;
		return true;
	case KEY_DOWN:
		if ((t->y + (x - 2)) >= (nr_signals - 1))
			break;
		if (y == (t->r - 1)) {
			t->y++;
			return true;
		}
		form_driver(t->form, REQ_DOWN_FIELD);
		break;
	case KEY_NPAGE:
		if ((t->y + (x - 2) + (t->r - 2)) > (nr_signals - 1))
			break;
		t->y += (t->r - 2);
		return true;
	case KEY_END:
// TODO: move cursor to top entry
		t->y = nr_signals - 1;
		return true;
	case KEY_LEFT:
		form_driver(t->form, REQ_LEFT_FIELD);
		break;
	case KEY_RIGHT:
		form_driver(t->form, REQ_RIGHT_FIELD);
		break;
	case KEY_ENTER:
	case '\r':
	case '\n':
		if (t->action)
			t->action(t, v, x, y);
		break;
	default:
		if (!t->driver || t->driver(t, k))
			form_driver(t->form, k);
		break;
	}

	return false;
}

/*******************************************************************************
 *
 ******************************************************************************/

static void
ui_menu_redraw(struct ui_window *w)
{
	const char *name = "nVPerfMon";
	mvwaddstr(w->win, 0, getmaxx(w->win) - strlen(name) - 1, name);
}

static struct ui_window
ui_menu_win = {
	.colour = UI_BLACK_GREEN,
	.redraw = ui_menu_redraw,
	.driver = NULL,
};

/*******************************************************************************
 *
 ******************************************************************************/

struct ui_perfmon_dom {
	struct list_head head;
	struct list_head signals;
	struct list_head perfdoms;
	u8 id;
};

struct ui_perfmon_sig {
	struct list_head head;
	char *name;
	u8 signal;
};

struct ui_main {
	struct list_head head;
	struct ui_perfmon_sig *sig;
	u32 clk;
	u32 ctr;
	u64 incr;
};

struct ui_perfdom {
	struct nvif_object object;
	struct list_head head;
	struct ui_main *ctr[4];
	u32 handle;
};

static struct list_head ui_main_list = LIST_HEAD_INIT(ui_main_list);
static struct list_head ui_doms_list = LIST_HEAD_INIT(ui_doms_list);
static struct list_head ui_perfdom_list = LIST_HEAD_INIT(ui_perfdom_list);
static u32 ui_main_handle = 0xc0000000;

static void
ui_main_remove(struct ui_main *item)
{
	list_del(&item->head);
	free(item);
}

static void
ui_perfmon_query_signals(struct ui_perfmon_dom *dom)
{
	struct nvif_perfmon_query_signal_v0 args = {};
	struct ui_perfmon_sig *sig;
	int ret;

	args.domain = dom->id;
	do {
		u16 prev_iter = args.iter;

		args.name[0] = '\0';
		ret = nvif_mthd(&perfmon, NVIF_PERFMON_V0_QUERY_SIGNAL,
				&args, sizeof(args));
		assert(ret == 0);

		if (prev_iter) {
			nr_signals++;
			sig = calloc(1, sizeof(*sig));
			sig->signal = args.signal;
			sig->name = malloc(sizeof(args.name));
			strncpy(sig->name, args.name, sizeof(args.name));
			list_add_tail(&sig->head, &dom->signals);

			args.iter = prev_iter;
			ret = nvif_mthd(&perfmon, NVIF_PERFMON_V0_QUERY_SIGNAL,
					&args, sizeof(args));
			assert(ret == 0);
		}
	} while (args.iter != 0xffff);
}

static void
ui_perfmon_query_domains(void)
{
	struct nvif_perfmon_query_domain_v0 args = {};
	struct ui_perfmon_dom *dom;
	int ret;

	assert(ret == 0);
	do {
		u8 prev_iter = args.iter;

		ret = nvif_mthd(&perfmon, NVIF_PERFMON_V0_QUERY_DOMAIN,
				&args, sizeof(args));
		assert(ret == 0);

		if (prev_iter) {
			dom = calloc(1, sizeof(*dom));
			dom->id = args.id;
			INIT_LIST_HEAD(&dom->signals);
			INIT_LIST_HEAD(&dom->perfdoms);
			list_add_tail(&dom->head, &ui_doms_list);

			args.iter = prev_iter;
			ret = nvif_mthd(&perfmon, NVIF_PERFMON_V0_QUERY_DOMAIN,
					&args, sizeof(args));
			assert(ret == 0);

			/* query available signals for the domain */
			ui_perfmon_query_signals(dom);
		}
	} while (args.iter != 0xff);
}

static void
ui_perfdom_init(struct ui_perfdom *dom)
{
	struct nvif_perfdom_init args = {};
	int ret;

	ret = nvif_mthd(&dom->object, NVIF_PERFDOM_V0_INIT,
			&args, sizeof(args));
	assert(ret == 0);
}

static void
ui_perfdom_sample(struct ui_perfdom *dom)
{
	struct nvif_perfdom_sample args = {};
	int ret;

	ret = nvif_mthd(&dom->object, NVIF_PERFDOM_V0_SAMPLE,
			&args, sizeof(args));
	assert(ret == 0);
}

static void
ui_perfdom_read(struct ui_perfdom *dom)
{
	struct nvif_perfdom_read_v0 args = {};
	int ret, i;

	ret = nvif_mthd(&dom->object, NVIF_PERFDOM_V0_READ,
			&args, sizeof(args));
	assert(ret == 0 || ret == -EAGAIN);

	if (ret == 0) {
		for (i = 0; i < 4; i++) {
			if (!dom->ctr[i])
				continue;
			dom->ctr[i]->ctr   = args.ctr[i];
			dom->ctr[i]->incr += args.ctr[i];
			dom->ctr[i]->clk   = args.clk;
		}
	}
}

static void
ui_perfmon_init(void)
{
	int ret;

	ret = nvif_object_init(&device->object, 0xdeadbeef,
			       NVIF_CLASS_PERFMON, NULL, 0, &perfmon);
	assert(ret == 0);

	/* query available domains for the device */
	ui_perfmon_query_domains();
}

static void
ui_perfmon_free_signals(struct ui_perfmon_dom *dom)
{
	struct ui_perfmon_sig *sig, *next;

	list_for_each_entry_safe(sig, next, &dom->signals, head) {
		list_del(&sig->head);
		free(sig->name);
		free(sig);
	}
}

static void
ui_perfmon_free_perfdoms(struct ui_perfmon_dom *dom)
{
	struct ui_perfdom *perfdom, *next;

	list_for_each_entry_safe(perfdom, next, &dom->perfdoms, head) {
		nvif_object_fini(&perfdom->object);
		list_del(&perfdom->head);
		free(perfdom);
	}
}

static void
ui_perfmon_fini(void)
{
	struct ui_perfmon_dom *dom, *next;

	list_for_each_entry_safe(dom, next, &ui_doms_list, head) {
		ui_perfmon_free_perfdoms(dom);
		ui_perfmon_free_signals(dom);
		list_del(&dom->head);
		free(dom);
	}

	nvif_object_fini(&perfmon);
}

static void
ui_main_select(void)
{
	struct ui_main *item, *temp;
	struct ui_perfmon_dom *dom;
	struct ui_perfmon_sig *sig;
	struct ui_perfdom *perfdom;
	int ret;
	int i;

	list_for_each_entry_safe(item, temp, &ui_main_list, head) {
		ui_main_remove(item);
	}

	list_for_each_entry(dom, &ui_doms_list, head) {
		list_for_each_entry(sig, &dom->signals, head) {
			bool found = false;

			item = calloc(1, sizeof(*item));
			item->sig = sig;
			list_add_tail(&item->head, &ui_main_list);

			/* find a slot */
			list_for_each_entry(perfdom, &dom->perfdoms, head) {
				for (i = 0; i < 4; i++) {
					if (!perfdom->ctr[i]) {
						perfdom->ctr[i] = item;
						found = true;
						break;
					}
				}
			}

			if (!found) {
				/* no free slots, create a new perfdom */
				perfdom = calloc(1, sizeof(*perfdom));
				perfdom->handle = ui_main_handle++;
				perfdom->ctr[0] = item;
				list_add_tail(&perfdom->head, &dom->perfdoms);
			}
		}

		/* init perfdom objects */
		list_for_each_entry(perfdom, &dom->perfdoms, head) {
			struct nvif_perfdom_v0 args = {};
			int i;

			args.domain = dom->id;
			for (i = 0; i < 4; i++) {
				struct ui_main *ctr = perfdom->ctr[i];
				if (!ctr)
					continue;
				args.ctr[i].signal[0] = ctr->sig->signal;
				args.ctr[i].logic_op  = 0xaaaa;
			}

			ret = nvif_object_init(&perfmon, perfdom->handle,
					       NVIF_CLASS_PERFDOM,
					       &args, sizeof(args),
					       &perfdom->object);
			assert(ret == 0);
		}
	}
}

static void
ui_main_alarm_handler(int signal)
{
	struct ui_perfmon_dom *dom;
	struct ui_perfdom *perfdom;
	bool sampled = false;

	if (list_empty(&ui_main_list))
		ui_main_select();

	list_for_each_entry(dom, &ui_doms_list, head) {
		if (list_empty(&dom->perfdoms))
			continue;

		perfdom = list_first_entry(&dom->perfdoms,
					   typeof(*perfdom), head);

		/* sample previous batch of counters */
		if (!sampled) {
			ui_perfdom_sample(perfdom);
			sampled = true;
		}

		/* read previous batch of counters */
		ui_perfdom_read(perfdom);

		/* setup next batch of counters for sampling */
		list_move_tail(&perfdom->head, &dom->perfdoms);
		perfdom = list_first_entry(&dom->perfdoms,
					   typeof(*perfdom), head);
		ui_perfdom_init(perfdom);
	}
}

static struct sigaction
ui_main_alarm = {
	.sa_handler = ui_main_alarm_handler,
};

static char *
ui_main_layout(struct ui_table *t)
{
	return "\x10\x00\x01";
}

static void
ui_main_action(struct ui_table *t, FIELD *f, int x, int y)
{
	void *priv = field_userptr(f);
	(void)priv;
}

static void
ui_main_redraw(struct ui_table *t)
{
	struct ui_main *item;
	FIELD **f = t->data;
	char b[128];
	int y;

	set_field_buffer(f[1], 0, "   Samples      Count      %            Total");
	f += t->c * 2;
// TODO: move cursor to top entry

	y = -1;
	list_for_each_entry(item, &ui_main_list, head) {
		if (++y >= t->y)
			break;
	}

	y = 2;
	list_for_each_entry_from(item, &ui_main_list, head) {
		set_field_buffer(f[0], 0, item->sig->name);
		set_field_userptr(f[0], item);
		field_opts_on(f[0], O_VISIBLE | O_ACTIVE);

		snprintf(b, sizeof(b), "%10u %10u %6.2f %16llx",
			    item->clk, item->ctr,
			    (float)item->ctr * 100.0 / item->clk, item->incr);
		set_field_buffer(f[1], 0, b);
		field_opts_on(f[1], O_VISIBLE);

		if (++y == t->r)
			break;
		f += t->c;
	}

	for (; y < t->r; y++) {
		field_opts_off(f[0], O_VISIBLE | O_ACTIVE);
		field_opts_off(f[1], O_VISIBLE);
		set_field_userptr(f[0], NULL);
		f += t->c;
	}
}

static bool
ui_main_driver(struct ui_window *w, int k)
{
	struct ui_table *t = (void *)w;
	struct ui_main *item, *temp;
	FIELD *f;

	switch (k) {
	case KEY_DC:
	case KEY_DL:
		f = current_field(t->form);
		item = field_userptr(f);
		if (item) {
			ui_main_remove(item);
			return true;
		}
		break;
	case 'x':
		list_for_each_entry_safe(item, temp, &ui_main_list, head) {
			if (item->incr == 0)
				ui_main_remove(item);
		}
		break;
	default:
		return ui_table_driver(w, k);
	}

	return false;
}

static int
ui_main_create(struct ui_window *win, int c, int r)
{
	int ret = ui_table_create(win, c, r);
	if (ret == 0) {
		sigaction(SIGALRM, &ui_main_alarm, 0);
		ualarm(1, 999999);
	}
	return ret;
}

static struct ui_table
ui_main_f = {
	.w.status = "main",
	.w.colour = UI_DEFAULT,
	.w.create = ui_main_create,
	.w.destroy = ui_table_destroy,
	.w.redraw = ui_table_redraw,
	.w.driver = ui_main_driver,
	.layout = ui_main_layout,
	.action = ui_main_action,
	.redraw = ui_main_redraw,
};

/*******************************************************************************
 *
 ******************************************************************************/

static void
ui_stat_redraw(struct ui_window *w)
{
}

static struct ui_window
ui_stat_win = {
	.colour = UI_BLACK_GREEN,
	.redraw = ui_stat_redraw,
	.driver = NULL,
};

/*******************************************************************************
 *
 ******************************************************************************/

static struct ui_layout {
	struct ui_window *w;
	int parent;
	int horiz;
	int percent;
	int adjust;
	int border;
} ui[] = {
	{ &ui_menu_win, -1, 0,   0, +1, 0 },
	{ &ui_main_f.w, -1, 0, 100, -2, 0 },
	{ &ui_stat_win, -1, 0,   0, +1, 0 },
	{}
}, *active = &ui[1];

static void
ui_redraw_win(struct ui_window *w)
{
	wclear(w->win);
	if (w->redraw)
		w->redraw(w);
	wrefresh(w->win);
}

static void
ui_active(int adjust)
{
	do {
		if ((active += adjust)->w == NULL) {
			active = &ui[0];
			adjust = 1;
		}
	} while(!active->w->driver);
	wrefresh(active->w->win);
}

static void
ui_redraw(void)
{
	struct ui_layout *l = ui - 1;
	struct ui_window *w;

	clear();
	refresh();

	while ((w = (++l)->w))
		ui_redraw_win(w);
	ui_active(0);
}

static void
ui_create(void)
{
	struct ui_layout *l = ui - 1;
	struct ui_window *w;
	WINDOW *p = stdscr;
	int mc = COLS, mr = LINES;
	int ac = 0, ar = 0;
	int x, y, c, r;
	int lp = -1;

	refresh();

	while ((w = (++l)->w)) {
		if (l->parent != lp) {
			 p = ui[l->parent].w->win;
			mc = getmaxx(p);
			mr = getmaxy(p);
			lp = l->parent;
			ac = ar = 0;
		}

		if (l->horiz) {
			if ((c = l->percent)) {
				if ((l + 1)->parent == l->parent)
					c = ((mc * l->percent) / 100);
				else
					c = mc - ac;
			}
			c = c + l->adjust;
			r = mr + (l->adjust * l->border);
			y = 0;
			x = ac; ac += c;
		} else {
			c = mc + (l->adjust * l->border);
			if ((r = l->percent)) {
				if ((l + 1)->parent == l->parent)
					r = ((mr * l->percent) / 100);
				else
					r = mr - ar;
			}
			r = r + l->adjust;
			x = 0;
			y = ar; ar += r;
		}

		x += l->border;
		y += l->border;

		w->win = derwin(p, r, c, y, x);
		wbkgd(w->win, COLOR_PAIR(w->colour));
		if (w->create)
			w->create(w, c, r);
	}

	ui_redraw();
}

static void
ui_destroy(void)
{
	struct ui_layout *l = ui + ARRAY_SIZE(ui);
	struct ui_window *w;

	while ((w = (--l)->w)) {
		if (w->destroy)
			w->destroy(w);
		delwin(w->win);
		w->win = NULL;
	}
}

static void
ui_resize(void)
{
	ui_destroy();
	ui_create();
}

int
main(int argc, char **argv)
{
	int ret, c, k;
	int scan = 0;

	while ((c = getopt(argc, argv, "s"U_GETOPT)) != -1) {
		switch (c) {
		case 's':
			scan = 1;
			break;
		default:
			if (!u_option(c))
				return 1;
			break;
		}
	}

	ret = u_device(NULL, argv[0], "error", true, true,
		       (1ULL << NVKM_SUBDEV_TIMER) |
		       (1ULL << NVKM_ENGINE_PM),
		       0x00000000, &client, device);
	if (ret)
		return ret;

	if (scan) {
		fprintf(stderr, "unimplemented\n");
		return 1;
	}

	ui_perfmon_init();

	initscr();
	keypad(stdscr, TRUE);
	nonl();
	cbreak();
	noecho();

	if (has_colors())
		start_color();
	init_pair(UI_BLACK_GREEN, COLOR_BLACK, COLOR_GREEN);

	ui_create();

	while ((k = getch()) != '\x1b') {
		switch (k) {
		case KEY_RESIZE:
			ui_resize();
			break;
		default:
			active->w->driver(active->w, k);
			break;
		}

		active->w->redraw(active->w);
	}

	ui_destroy();
	endwin();
	ui_perfmon_fini();

	nvif_device_fini(device);
	nvif_client_fini(&client);
	return 0;
}
