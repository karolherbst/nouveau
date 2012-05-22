#ifndef __NOUVEAU_MEMOBJ_H__
#define __NOUVEAU_MEMOBJ_H__

#include <core/object.h>
#include <core/mm.h>

struct nouveau_memobj {
	struct nouveau_object base;
	struct nouveau_mm heap;
	u32 *suspend;
	u64 addr;
};

static inline struct nouveau_memobj *
nv_memobj(void *obj)
{
#if CONFIG_NOUVEAU_DEBUG >= NV_DBG_PARANOIA
	if (unlikely(!nv_iclass(obj, NV_MEMOBJ_CLASS)))
		nv_assert("BAD CAST -> NvMemObj, %08x", nv_hclass(obj));
#endif
	return obj;
}

#define nouveau_memobj_create(p,e,c,d)                                         \
	nouveau_object_create_((p), (e), (c), NV_MEMOBJ_CLASS,                 \
			       sizeof(**d), (void **)d)
#define nouveau_memobj_destroy(p) nouveau_object_destroy(&(p)->base)

int nouveau_memobj_init(struct nouveau_memobj *);
int nouveau_memobj_fini(struct nouveau_memobj *, bool suspend);

#endif
