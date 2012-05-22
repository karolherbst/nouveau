noinst_LTLIBRARIES = libpciaccessos.la

libpciaccessos_la_CPPFLAGS = -I${top_srcdir}/nvkm/include \
			     -I${top_srcdir}/nvkm
libpciaccessos_la_CFLAGS = @PCIACCESS_CFLAGS@
libpciaccessos_la_LDFLAGS = @PCIACCESS_LIBS@ -lpthread
libpciaccessos_la_SOURCES = main.c
