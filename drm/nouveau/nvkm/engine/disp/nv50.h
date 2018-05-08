/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __NV50_DISP_H__
#define __NV50_DISP_H__
#define nv50_disp(p) container_of((p), struct nv50_disp, base)
#include "priv.h"
struct nvkm_head;

struct nv50_disp {
	const struct nv50_disp_func *func;
	struct nvkm_disp base;

	struct workqueue_struct *wq;
	struct work_struct supervisor;
	u32 super;

	struct nvkm_event uevent;

	struct {
		unsigned long mask;
		int nr;
	} head, dac;

	struct {
		unsigned long mask;
		int nr;
		u32 lvdsconf;
	} sor;

	struct {
		unsigned long mask;
		int nr;
		u8 type[3];
	} pior;

	struct nvkm_gpuobj *inst;
	struct nvkm_ramht *ramht;

	struct nv50_disp_chan *chan[21];
};

void nv50_disp_super_1(struct nv50_disp *);
void nv50_disp_super_1_0(struct nv50_disp *, struct nvkm_head *);
void nv50_disp_super_2_0(struct nv50_disp *, struct nvkm_head *);
void nv50_disp_super_2_1(struct nv50_disp *, struct nvkm_head *);
void nv50_disp_super_2_2(struct nv50_disp *, struct nvkm_head *);
void nv50_disp_super_3_0(struct nv50_disp *, struct nvkm_head *);

int nv50_disp_new_(const struct nv50_disp_func *, struct nvkm_device *,
		   int index, struct nvkm_disp **);

struct nv50_disp_func {
	int (*init)(struct nv50_disp *);
	void (*fini)(struct nv50_disp *);
	void (*intr)(struct nv50_disp *);
	void (*intr_error)(struct nv50_disp *, int chid);

	const struct nvkm_event_func *uevent;
	void (*super)(struct work_struct *);

	const struct nvkm_disp_oclass *root;

	struct {
		int (*cnt)(struct nvkm_disp *, unsigned long *mask);
		int (*new)(struct nvkm_disp *, int id);
	} head, dac, sor, pior;
};

int nv50_disp_init(struct nv50_disp *);
void nv50_disp_fini(struct nv50_disp *);
void nv50_disp_intr(struct nv50_disp *);
void nv50_disp_super(struct work_struct *);

int gf119_disp_init(struct nv50_disp *);
void gf119_disp_fini(struct nv50_disp *);
void gf119_disp_intr(struct nv50_disp *);
void gf119_disp_super(struct work_struct *);
void gf119_disp_intr_error(struct nv50_disp *, int);

void nv50_disp_dptmds_war_2(struct nv50_disp *, struct dcb_output *);
void nv50_disp_dptmds_war_3(struct nv50_disp *, struct dcb_output *);
void nv50_disp_update_sppll1(struct nv50_disp *);
#endif
