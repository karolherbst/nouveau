LIBNVIF_CC := $(CFLAGS) -fPIC
LIBNVIF_LD := $(LDFLAGS) -shared -lpciaccess -lpthread -ldrm

src  := $(drm)
include $(src)/nvif/Kbuild
include $(src)/nvkm/Kbuild

fucs := $(drm)/nvkm/engine/ce/fuc/nva3.fuc3.h \
	$(drm)/nvkm/engine/ce/fuc/nvc0.fuc3.h \
	$(drm)/nvkm/engine/graph/fuc/hubnvc0.fuc3.h \
	$(drm)/nvkm/engine/graph/fuc/hubnvd7.fuc3.h \
	$(drm)/nvkm/engine/graph/fuc/hubnve0.fuc3.h \
	$(drm)/nvkm/engine/graph/fuc/hubnvf0.fuc3.h \
	$(drm)/nvkm/engine/graph/fuc/hubnv108.fuc5.h \
	$(drm)/nvkm/engine/graph/fuc/hubgm107.fuc5.h \
	$(drm)/nvkm/engine/graph/fuc/gpcnvc0.fuc3.h \
	$(drm)/nvkm/engine/graph/fuc/gpcnvd7.fuc3.h \
	$(drm)/nvkm/engine/graph/fuc/gpcnve0.fuc3.h \
	$(drm)/nvkm/engine/graph/fuc/gpcnvf0.fuc3.h \
	$(drm)/nvkm/engine/graph/fuc/gpcnv108.fuc5.h \
	$(drm)/nvkm/engine/graph/fuc/gpcgm107.fuc5.h \
	$(drm)/nvkm/subdev/pmu/fuc/nva3.fuc3.h \
	$(drm)/nvkm/subdev/pmu/fuc/nvc0.fuc3.h \
	$(drm)/nvkm/subdev/pmu/fuc/nvd0.fuc4.h \
	$(drm)/nvkm/subdev/pmu/fuc/nv108.fuc5.h \
	$(drm)/nvkm/engine/sec/fuc/nv98.fuc0s.h
drms := $(addprefix $(lib)/, $(nvif-y)) \
	$(addprefix $(lib)/, $(nvkm-y))
srcs := $(lib)/drm.o \
	$(lib)/intr.o \
	$(lib)/main.o \
	$(lib)/null.o
outp := $(lib)/libnvif.so

deps-fuc := $(fucs:$(drm)/%.h=$(lib)/%.d)
deps-drm := $(drms:%.o=%.d)
deps-src := $(srcs:%.o=%.d)

$(deps-fuc): $(lib)/%.d : $(drm)/%
	@mkdir -p $(dir $@)
	@$(CC) $(LIBNVIF_CC) -E -MM -MP -MT $<.h -MF $@ -xc $<
$(deps-drm): $(lib)/%.d : $(drm)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(LIBNVIF_CC) -E -MM -MP -MT $(patsubst %.d,%.o,$@) -MF $@ $<
$(deps-src): $(lib)/%.d : $(lib)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(LIBNVIF_CC) -E -MM -MP -MT $(patsubst %.d,%.o,$@) -MF $@ $<

$(filter %.fuc0s.h,$(fucs)): %.fuc0s.h : %.fuc0s
	@echo "  FUC0S    "$@
	@$(call ENVYPP,$<) | $(ENVYAS) -a -w -mfuc -Vfuc0 -Fcrypt -o $@
$(filter %.fuc3.h,$(fucs)): %.fuc3.h : %.fuc3
	@echo "  FUC3     "$@
	@$(call ENVYPP,$<) | $(ENVYAS) -a -w -mfuc -Vfuc3 -o $@
$(filter %.fuc4.h,$(fucs)): %.fuc4.h : %.fuc4
	@echo "  FUC4     "$@
	@$(call ENVYPP,$<) | $(ENVYAS) -a -w -mfuc -Vfuc4 -o $@
$(filter %.fuc5.h,$(fucs)): %.fuc5.h : %.fuc5
	@echo "  FUC5     "$@
	@$(call ENVYPP,$<) | $(ENVYAS) -a -w -mfuc -Vfuc5 -o $@

$(drms): $(lib)/%.o : $(drm)/%.c
	@echo "  CC       "$@
	@$(CC) $(LIBNVIF_CC) -o $@ -c $<
$(srcs): $(lib)/%.o : $(lib)/%.c
	@echo "  CC       "$@
	@$(CC) $(LIBNVIF_CC) -o $@ -c $<
$(outp): $(drms) $(srcs)
	@echo "  CCLD     "$@
	@$(CC) $(LIBNVIF_LD) -o $@ $^

deps += $(deps-fuc) $(deps-drm) $(deps-src)
objs += $(drms) $(srcs)
libs += $(outp)
fws  += $(fucs)
