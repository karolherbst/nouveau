#ifndef __NV50_KMS_CORE_H__
#define __NV50_KMS_CORE_H__
#include "disp.h"
#include "atom.h"

struct nv50_core {
	const struct nv50_core_func *func;
	struct nv50_dmac chan;
};

struct nv50_core_caps {
	struct {
		struct {
			uint16_t max_mhz;
			bool no_interlace;
		} dp;

		struct {
			uint16_t max_mhz;
		} lvds;

		struct {
			uint16_t max_mhz;
		} tmds;
	} sor[8];
};

int nv50_core_new(struct nouveau_drm *, struct nv50_core **);
void nv50_core_del(struct nv50_core **);

struct nv50_core_func {
	void (*init)(struct nv50_core *);
	void (*ntfy_init)(struct nouveau_bo *, u32 offset);
	int (*ntfy_wait_done)(struct nouveau_bo *, u32 offset,
			      struct nvif_device *);
	void (*update)(struct nv50_core *, u32 *interlock, bool ntfy);
	bool (*caps_fetch)(struct nv50_disp *);
	bool (*caps_parse)(struct nv50_disp *, struct nv50_core_caps *);

	const struct nv50_head_func *head;
	const struct nv50_outp_func {
		void (*ctrl)(struct nv50_core *, int or, u32 ctrl,
			     struct nv50_head_atom *);
	} *dac, *pior, *sor;
};

int core507d_new(struct nouveau_drm *, s32, struct nv50_core **);
int core507d_new_(const struct nv50_core_func *, struct nouveau_drm *, s32,
		  struct nv50_core **);
void core507d_init(struct nv50_core *);
void core507d_ntfy_init(struct nouveau_bo *, u32);
int core507d_ntfy_wait_done(struct nouveau_bo *, u32, struct nvif_device *);
void core507d_update(struct nv50_core *, u32 *, bool);
bool core507d_caps_fetch(struct nv50_disp *);

extern const struct nv50_outp_func dac507d;
extern const struct nv50_outp_func sor507d;
extern const struct nv50_outp_func pior507d;

int core827d_new(struct nouveau_drm *, s32, struct nv50_core **);

int core907d_new(struct nouveau_drm *, s32, struct nv50_core **);
extern const struct nv50_outp_func dac907d;
extern const struct nv50_outp_func sor907d;
bool core907d_caps_parse(struct nv50_disp *, struct nv50_core_caps *);

int core917d_new(struct nouveau_drm *, s32, struct nv50_core **);

int core957d_new(struct nouveau_drm *, s32, struct nv50_core **);

int corec37d_new(struct nouveau_drm *, s32, struct nv50_core **);
extern const struct nv50_outp_func sorc37d;
#endif
