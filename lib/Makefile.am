noinst_LTLIBRARIES = libpciaccessos.la

libpciaccessos_la_CPPFLAGS = -I${top_srcdir}/nvkm/include \
			     -I${top_srcdir}/nvkm \
			     -I${top_srcdir} \
			     -I/usr/include/libdrm
libpciaccessos_la_CFLAGS = @PCIACCESS_CFLAGS@
libpciaccessos_la_LIBADD = @PCIACCESS_LIBS@ -lpthread -ldrm \
			   $(top_srcdir)/nvkm/libnvkm.la
libpciaccessos_la_SOURCES = intr.c \
			    main.c \
			    null.c \
			    kern.c
