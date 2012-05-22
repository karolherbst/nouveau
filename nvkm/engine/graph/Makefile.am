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

fuc/hubnvc0.fuc.h: fuc/nvc0.fuc fuc/hubnvc0.fuc
	cd fuc && \
	m4 hubnvc0.fuc | envyas -a -w -m fuc -V fuc3 -o hubnvc0.fuc.h && \
	cd ..

fuc/gpcnvc0.fuc.h: fuc/nvc0.fuc fuc/gpcnvc0.fuc
	cd fuc && \
	m4 gpcnvc0.fuc | envyas -a -w -m fuc -V fuc3 -o gpcnvc0.fuc.h && \
	cd ..

fuc/hubnve0.fuc.h: fuc/nve0.fuc fuc/hubnve0.fuc
	cd fuc && \
	m4 hubnve0.fuc | envyas -a -w -m fuc -V fuc3 -o hubnve0.fuc.h && \
	cd ..

fuc/gpcnve0.fuc.h: fuc/nve0.fuc fuc/gpcnve0.fuc
	cd fuc && \
	m4 gpcnve0.fuc | envyas -a -w -m fuc -V fuc3 -o gpcnve0.fuc.h && \
	cd ..

include $(srcdir)/../Makefile.engine
