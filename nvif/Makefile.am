lib_LTLIBRARIES = libnvif.la

# XXX: /lib shouldn't be here, but is needed while we include core headers
libnvif_la_CPPFLAGS = -I${top_srcdir}/nvkm/include \
		      -I${top_srcdir}/nvkm \
		      -I${top_srcdir}/lib \
		      -I${top_srcdir}
libnvif_la_LIBADD = $(top_srcdir)/lib/libpciaccessos.la
libnvif_la_SOURCES = object.c \
		     client.c \
		     device.c \
		     notify.c
