bin_PROGRAMS = \
	       nv_rd08 nv_rd16 nv_rd32 nv_wr08 nv_wr16 nv_wr32 \
	       nv_rf08 nv_rf16 nv_rf32 nv_wf08 nv_wf16 nv_wf32 \
	       nv_ri08 nv_ri16 nv_ri32 nv_wi08 nv_wi16 nv_wi32 \
	       nv_rv08 nv_rv16 nv_rv32 nv_wv08 nv_wv16 nv_wv32 \
	       nv_rs08 nv_rs16 nv_rs32 nv_ws08 nv_ws16 nv_ws32 \
	       nv_disp

AM_CPPFLAGS = -I$(top_srcdir)/nvkm/include \
	      -I$(top_srcdir)/nvkm \
	      -I$(top_srcdir)/lib/

LDADD = -lpciaccess \
	$(top_srcdir)/lib/libpciaccessos.la \
	$(top_srcdir)/nvkm/libnouveau.la
