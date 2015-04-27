/*
 * Copyright (c) 2015, NVIDIA CORPORATION. All rights reserved.
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
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#include <subdev/volt.h>
#ifdef __KERNEL__
#include <nouveau_platform.h>
#endif

#include "gk20a.h"

const struct cvb_coef gm20b_na_cvb_coef[] = {
	/* KHz,         c0,     c1,   c2,    c3,     c4,   c5 */
	/*  76800 */ {  814294, 8144, -940, 808, -21583, 226 },
	/* 153600 */ {  856185, 8144, -940, 808, -21583, 226 },
	/* 230400 */ {  898077, 8144, -940, 808, -21583, 226 },
	/* 307200 */ {  939968, 8144, -940, 808, -21583, 226 },
	/* 384000 */ {  981860, 8144, -940, 808, -21583, 226 },
	/* 460800 */ { 1023751, 8144, -940, 808, -21583, 226 },
	/* 537600 */ { 1065642, 8144, -940, 808, -21583, 226 },
	/* 614400 */ { 1107534, 8144, -940, 808, -21583, 226 },
	/* 691200 */ { 1149425, 8144, -940, 808, -21583, 226 },
	/* 768000 */ { 1191317, 8144, -940, 808, -21583, 226 },
	/* 844800 */ { 1233208, 8144, -940, 808, -21583, 226 },
	/* 921600 */ { 1275100, 8144, -940, 808, -21583, 226 },
	/* 998400 */ { 1316991, 8144, -940, 808, -21583, 226 },
};

const struct cvb_coef gm20b_cvb_coef[] = {
	/* KHz,             c0,      c1,   c2 */
	/*  76800 */ { 1786666,  -85625, 1632 },
	/* 153600 */ { 1846729,  -87525, 1632 },
	/* 230400 */ { 1910480,  -89425, 1632 },
	/* 307200 */ { 1977920,  -91325, 1632 },
	/* 384000 */ { 2049049,  -93215, 1632 },
	/* 460800 */ { 2122872,  -95095, 1632 },
	/* 537600 */ { 2201331,  -96985, 1632 },
	/* 614400 */ { 2283479,  -98885, 1632 },
	/* 691200 */ { 2369315, -100785, 1632 },
	/* 768000 */ { 2458841, -102685, 1632 },
	/* 844800 */ { 2550821, -104555, 1632 },
	/* 921600 */ { 2647676, -106455, 1632 },
};

#define MAX_SPEEDO 4

const int speedo_to_vmin[MAX_SPEEDO+1] = {
	/*   0,      1,      2,      3,      4, */
	950000, 840000, 800000, 840000, 800000,
};

static int
gm20b_volt_ctor(struct nvkm_object *parent, struct nvkm_object *engine,
		struct nvkm_oclass *oclass, void *data, u32 size,
		struct nvkm_object **pobject)
{
	struct gk20a_volt_priv *priv;
	struct nvkm_volt *volt;
	struct nouveau_platform_device *plat;
	const struct cvb_coef *coef_table;
	int i, ret, uv;

	ret = nvkm_volt_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	volt = &priv->base;

	plat = nv_device_to_platform(nv_device(parent));

	if (plat->gpu_speedo_id > MAX_SPEEDO) {
		nv_error(priv, "Unsupported Speedo = %d\n", plat->gpu_speedo_id);
		return -EINVAL;
	}

	uv = regulator_get_voltage(plat->gpu->vdd);
	nv_info(priv, "The default voltage is %duV\n", uv);

	priv->vdd = plat->gpu->vdd;
	priv->base.vid_get = gk20a_volt_vid_get;
	priv->base.vid_set = gk20a_volt_vid_set;
	priv->base.set_id = gk20a_volt_set_id;

	if (plat->gpu_speedo_id >= 1) {
		coef_table = gm20b_na_cvb_coef;
		volt->vid_nr = ARRAY_SIZE(gm20b_na_cvb_coef);
	} else {
		coef_table = gm20b_cvb_coef;
		volt->vid_nr = ARRAY_SIZE(gm20b_cvb_coef);
	}
	nv_debug(priv, "%s - vid_nr = %d\n", __func__, volt->vid_nr);
	for (i = 0; i < volt->vid_nr; i++) {
		volt->vid[i].vid = i;
		volt->vid[i].uv = gk20a_volt_calc_voltage((coef_table + i),
					plat->gpu_speedo_value);
		if (volt->vid[i].uv < speedo_to_vmin[plat->gpu_speedo_id])
			volt->vid[i].uv = speedo_to_vmin[plat->gpu_speedo_id];
		nv_debug(priv, "%2d: vid=%d, uv=%d\n", i, volt->vid[i].vid,
					volt->vid[i].uv);
	}

	return 0;
}

struct nvkm_oclass
gm20b_volt_oclass = {
	.handle = NV_SUBDEV(VOLT, 0x12b),
	.ofuncs = &(struct nvkm_ofuncs) {
		.ctor = gm20b_volt_ctor,
		.dtor = _nvkm_volt_dtor,
		.init = _nvkm_volt_init,
		.fini = _nvkm_volt_fini,
	},
};
