noinst_LTLIBRARIES = libgraph.la

BUILT_SOURCES = fuc/hubnvc0.fuc.h \
		fuc/gpcnvc0.fuc.h \
		fuc/hubnve0.fuc.h \
		fuc/gpcnve0.fuc.h
CLEANFILES = ${BUILT_SOURCES}

libgraph_la_SOURCES = ${BUILT_SOURCES} \
		      ctxnv40.c \
		      ctxnv50.c \
		      ctxnvc0.c \
		      ctxnve0.c \
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
		      nve0.c

$(filter %.fuc.h,$(BUILT_SOURCES)): %.fuc.h: %.fuc fuc/com.fuc fuc/hub.fuc fuc/gpc.fuc
	cpp -Ifuc -CC $< | cpp | sed -e '/^#/d' \
	| envyas -a -w -m fuc -V fuc3 -o $@

include $(srcdir)/../Makefile.engine
