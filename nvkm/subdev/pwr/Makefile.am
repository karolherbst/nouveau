noinst_LTLIBRARIES = libpwr.la

BUILT_SOURCES = fuc/nva3.fuc.h \
		fuc/nvc0.fuc.h \
		fuc/nvd0.fuc.h \
		fuc/nv108.fuc.h
CLEANFILES = ${BUILT_SOURCES}

libpwr_la_SOURCES = base.c \
		    memx.c \
		    nva3.c \
		    nvc0.c \
		    nvd0.c \
		    gk104.c \
		    nv108.c

FUC_COMMON = fuc/os.h \
	     fuc/macros.fuc \
	     fuc/kernel.fuc \
	     fuc/idle.fuc \
	     fuc/host.fuc \
	     fuc/memx.fuc \
	     fuc/perf.fuc \
	     fuc/i2c_.fuc \
	     fuc/test.fuc \
	     fuc/arith.fuc

fuc/nva3.fuc.h: fuc/nva3.fuc ${FUC_COMMON}
	cpp -Ifuc -CC fuc/nva3.fuc | cpp \
	| sed -e '/^#/d' \
	| envyas -a -w -m fuc -V fuc3 -o fuc/nva3.fuc.h
fuc/nvc0.fuc.h: fuc/nvc0.fuc ${FUC_COMMON}
	cpp -Ifuc -CC fuc/nvc0.fuc | cpp \
	| sed -e '/^#/d' \
	| envyas -a -w -m fuc -V fuc3 -o fuc/nvc0.fuc.h
fuc/nvd0.fuc.h: fuc/nvd0.fuc ${FUC_COMMON}
	cpp -Ifuc -CC fuc/nvd0.fuc | cpp \
	| sed -e '/^#/d' \
	| envyas -a -w -m fuc -V fuc4 -o fuc/nvd0.fuc.h
fuc/nv108.fuc.h: fuc/nv108.fuc ${FUC_COMMON}
	cpp -Ifuc -CC fuc/nv108.fuc | cpp \
	| sed -e '/^#/d' \
	| envyas -a -w -m fuc -V fuc5 -o fuc/nv108.fuc.h

include $(srcdir)/../Makefile.subdev
