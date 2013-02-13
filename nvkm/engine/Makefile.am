SUBDIRS = dmaobj bsp copy crypt device disp fifo graph mpeg perfmon ppp \
	  software vp

noinst_LTLIBRARIES = libengine.la

libengine_la_SOURCES = falcon.c \
		       xtensa.c

libengine_la_LIBADD  = bsp/libbsp.la \
		       copy/libcopy.la \
		       crypt/libcrypt.la \
		       device/libdevice.la \
		       disp/libdisp.la \
		       dmaobj/libdmaobj.la \
		       fifo/libfifo.la \
		       graph/libgraph.la \
		       mpeg/libmpeg.la \
		       perfmon/libperfmon.la \
		       ppp/libppp.la \
		       software/libsoftware.la \
		       vp/libvp.la

include $(srcdir)/Makefile.engine
