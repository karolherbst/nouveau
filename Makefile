.PHONY: all build clean install
all: build

prefix ?= /usr/local
bindir ?= $(prefix)/bin
libdir ?= $(prefix)/lib

top := .
drm := $(top)/drm/nouveau
lib := $(top)/lib
bin := $(top)/bin

CFLAGS  ?= -O0 -ggdb3
CFLAGS  += -I$(lib)/include -I$(drm)/include -I$(drm)/include/nvkm \
	   -I$(drm)/nvkm -I/usr/include/libdrm \
	   -fno-strict-aliasing -Wall -Wundef -Wstrict-prototypes \
	   -DCONFIG_NOUVEAU_DEBUG=7 \
	   -DCONFIG_NOUVEAU_DEBUG_DEFAULT=3 \
	   -DCONFIG_NOUVEAU_DEBUG_MMU=y \
	   -DCONFIG_NOUVEAU_I2C_INTERNAL \
	   -DCONFIG_NOUVEAU_I2C_INTERNAL_DEFAULT \
	   -DCONFIG_NOUVEAU_PLATFORM_DRIVER=y \
	   -DCONFIG_AGP=y \
	   -DCONFIG_IOMMU_API=y
ENVYAS  ?= envyas
ENVYPP   = $(CC) -E -CC -xc $(1) | $(CC) -E - | sed -e "/^\#/d"
INSTALL ?= install

deps :=
objs :=
libs :=
bins :=
fws  :=

include $(lib)/Makefile
include $(bin)/Makefile

build: $(bins)

clean:
	@rm -f $(deps) $(objs) $(libs) $(bins)

clean-fw:
	@rm -f $(fws)

install-lib = $(INSTALL) -D -m 755 $(1) $(libdir);
install-bin = $(INSTALL) -D -m 755 $(1) $(bindir);
install:
	$(foreach lib,$(libs),$(call install-lib,$(lib)))
	ldconfig $(libdir)
	$(foreach bin,$(bins),$(call install-bin,$(bin)))

-include $(deps)
