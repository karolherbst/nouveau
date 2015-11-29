#ifndef __NVBIOS_BASECLOCK_H__
#define __NVBIOS_BASECLOCK_H__
struct nvbios_baseclk_header {
	u16 offset;

	u8 version;
	u8 hlen;
	u8 ecount;
	u8 elen;
	u8 scount;
	u8 slen;

	u8 base_id;
	u8 boost_id;
	u8 tdp_id;
};
struct nvbios_baseclk_entry {
	u8  pstate;
	u16 clock_mhz;
};
int nvbios_baseclock_parse(struct nvkm_bios *, struct nvbios_baseclk_header *);
int nvbios_baseclock_entry(struct nvkm_bios *, struct nvbios_baseclk_header *,
			   u8 idx, struct nvbios_baseclk_entry *);
#endif
