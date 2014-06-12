noinst_LTLIBRARIES = libgraph.la

BUILT_SOURCES = fuc/hubnvc0.fuc.h \
		fuc/gpcnvc0.fuc.h \
		fuc/hubnvd7.fuc.h \
		fuc/gpcnvd7.fuc.h \
		fuc/hubnve0.fuc.h \
		fuc/gpcnve0.fuc.h \
		fuc/hubnvf0.fuc.h \
		fuc/gpcnvf0.fuc.h \
		fuc/hubnv108.fuc5.h \
		fuc/gpcnv108.fuc5.h \
		fuc/hubgm107.fuc5.h \
		fuc/gpcgm107.fuc5.h
CLEANFILES = ${BUILT_SOURCES}

libgraph_la_SOURCES = ${BUILT_SOURCES} \
		      ctxnv40.c \
		      ctxnv50.c \
		      ctxnvc0.c \
		      ctxnvc1.c \
		      ctxnvc4.c \
		      ctxnvc8.c \
		      ctxnvd7.c \
		      ctxnvd9.c \
		      ctxnve4.c \
		      ctxgk20a.c \
		      ctxnvf0.c \
		      ctxgk110b.c \
		      ctxnv108.c \
		      ctxgm107.c \
		      nv04.c \
		      nv10.c \
		      nv20.c \
		      nv25.c \
		      nv2a.c \
		      nv30.c \
		      nv34.c \
		      nv35.c \
		      nv40.c \
		      nv50.c \
		      nvc0.c \
		      nvc1.c \
		      nvc4.c \
		      nvc8.c \
		      nvd7.c \
		      nvd9.c \
		      nve4.c \
		      gk20a.c \
		      nvf0.c \
		      gk110b.c \
		      nv108.c \
		      gm107.c

$(filter %.fuc.h,$(BUILT_SOURCES)): %.fuc.h: %.fuc fuc/com.fuc fuc/hub.fuc fuc/gpc.fuc fuc/macros.fuc
	cpp -Ifuc -CC $< | cpp | sed -e '/^#/d' \
	| envyas -a -w -m fuc -V fuc3 -o $@
$(filter %.fuc5.h,$(BUILT_SOURCES)): %.fuc5.h: %.fuc5 fuc/com.fuc fuc/hub.fuc fuc/gpc.fuc
	cpp -Ifuc -CC $< | cpp | sed -e '/^#/d' \
	| envyas -a -w -m fuc -V fuc5 -o $@

include $(srcdir)/../Makefile.engine
