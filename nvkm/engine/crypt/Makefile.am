noinst_LTLIBRARIES = libcrypt.la

BUILT_SOURCES = fuc/nv98.fuc.h
CLEANFILES = ${BUILT_SOURCES}

libcrypt_la_SOURCES = ${BUILT_SOURCES} \
		      nv84.c \
		      nv98.c

fuc/nv98.fuc.h: fuc/nv98.fuc
	m4 fuc/nv98.fuc | envyas -a -w -m fuc -V fuc0 -F crypt -o fuc/nv98.fuc.h

include $(srcdir)/../Makefile.engine
