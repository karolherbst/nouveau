noinst_LTLIBRARIES = libcopy.la

BUILT_SOURCES = fuc/nva3.fuc.h \
		fuc/nvc0.fuc.h
CLEANFILES = ${BUILT_SOURCES}

libcopy_la_SOURCES = ${BUILT_SOURCES} \
		     nva3.c \
		     nvc0.c \
		     nve0.c

fuc/nva3.fuc.h: fuc/nva3.fuc
	m4 -DNVA3 fuc/nva3.fuc | envyas -a -w -m fuc -V fuc3 -o fuc/nva3.fuc.h
fuc/nvc0.fuc.h: fuc/nva3.fuc
	m4 -DNVC0 fuc/nva3.fuc | envyas -a -w -m fuc -V fuc3 -o fuc/nvc0.fuc.h

include $(srcdir)/../Makefile.engine
