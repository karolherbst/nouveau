#ifndef __NVBIOS_THERMAL_POLICIES_H__
#define __NVBIOS_THERMAL_POLICIES_H__

struct nvbios_thermal_policies_header {
	u32 offset;

	u8 version;
	u8 hlen;
	u8 ecount;
	u8 elen;
};
struct nvbios_thermal_policies_entry {
	u8  mode;
	u16 t0;
	s16 down_offset;
	s16 up_offset;
};

int nvbios_thermal_policies_parse(struct nvkm_bios *,
				  struct nvbios_thermal_policies_header *);
int nvbios_thermal_policies_entry(struct nvkm_bios *,
				  struct nvbios_thermal_policies_header *,
				  u8 idx,
				  struct nvbios_thermal_policies_entry *);
#endif
