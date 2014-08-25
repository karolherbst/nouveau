AC_INIT([nouveau], 1.0.2)
AC_CONFIG_SRCDIR([configure.ac])
AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CC
AC_LANG_C
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

AM_INIT_AUTOMAKE
AM_SILENT_RULES([yes])

PKG_CHECK_MODULES(PCIACCESS, pciaccess)
AC_SUBST([PCIACCESS_CFLAGS])
AC_SUBST([PCIACCESS_LIBS])

AC_ARG_ENABLE([debug-level],
	      [AS_HELP_STRING([--enable-debug-level=LEVEL],
			      [select highest debug level to build support for
			       (fatal, error, warning, info, debug,
				trace, paranoia, spam) [default = debug]])],
	      [ debug=$enableval ],
	      [ debug=debug ])

AC_MSG_CHECKING([for maximum debug level to build])
if test "x$debug" = "xfatal"; then
	AC_DEFINE([CONFIG_NOUVEAU_DEBUG], [0])
elif test "x$debug" = "xerror"; then
	AC_DEFINE([CONFIG_NOUVEAU_DEBUG], [1])
elif test "x$debug" = "xwarning"; then
	AC_DEFINE([CONFIG_NOUVEAU_DEBUG], [2])
elif test "x$debug" = "xinfo"; then
	AC_DEFINE([CONFIG_NOUVEAU_DEBUG], [3])
elif test "x$debug" = "xdebug"; then
	AC_DEFINE([CONFIG_NOUVEAU_DEBUG], [4])
elif test "x$debug" = "xtrace"; then
	AC_DEFINE([CONFIG_NOUVEAU_DEBUG], [5])
elif test "x$debug" = "xparanoia"; then
	AC_DEFINE([CONFIG_NOUVEAU_DEBUG], [6])
elif test "x$debug" = "xspam"; then
	AC_DEFINE([CONFIG_NOUVEAU_DEBUG], [7])
else
	AC_MSG_ERROR([invalid debug level specified])
fi
AC_MSG_RESULT($debug)
AC_DEFINE([CONFIG_NOUVEAU_DEBUG_DEFAULT], [3])

AC_ARG_ENABLE([internal-bitbang],
	      [AS_HELP_STRING([--enable-internal-bitbang[[=default]]],
			      [enable use of internal i2c bit-banging algo ])],
	      [ bitbang=$enableval ],
	      [ bitbang=default ])

AC_MSG_CHECKING([whether to enable internal i2c bit-banging algo])
if test "x$bitbang" = "xdefault"; then
	AC_DEFINE([CONFIG_NOUVEAU_I2C_INTERNAL], [1])
	AC_DEFINE([CONFIG_NOUVEAU_I2C_INTERNAL_DEFAULT], [1])
	AC_MSG_RESULT([default])
elif test "x$bitbang" = "xyes"; then
	AC_DEFINE([CONFIG_NOUVEAU_I2C_INTERNAL], [1])
	AC_MSG_RESULT([yes])
else
	AC_MSG_RESULT([no])
fi

AC_OUTPUT( Makefile \
	   nvkm/Makefile \
	   nvkm/core/Makefile \
	   nvkm/subdev/Makefile \
	   nvkm/subdev/bar/Makefile \
	   nvkm/subdev/bios/Makefile \
	   nvkm/subdev/bus/Makefile \
	   nvkm/subdev/clock/Makefile \
	   nvkm/subdev/devinit/Makefile \
	   nvkm/subdev/fb/Makefile \
	   nvkm/subdev/fuse/Makefile \
	   nvkm/subdev/gpio/Makefile \
	   nvkm/subdev/i2c/Makefile \
	   nvkm/subdev/ibus/Makefile \
	   nvkm/subdev/instmem/Makefile \
	   nvkm/subdev/ltc/Makefile \
	   nvkm/subdev/mc/Makefile \
	   nvkm/subdev/mxm/Makefile \
	   nvkm/subdev/pwr/Makefile \
	   nvkm/subdev/therm/Makefile \
	   nvkm/subdev/timer/Makefile \
	   nvkm/subdev/vm/Makefile \
	   nvkm/subdev/volt/Makefile \
	   nvkm/engine/Makefile \
	   nvkm/engine/bsp/Makefile \
	   nvkm/engine/copy/Makefile \
	   nvkm/engine/crypt/Makefile \
	   nvkm/engine/device/Makefile \
	   nvkm/engine/disp/Makefile \
	   nvkm/engine/dmaobj/Makefile \
	   nvkm/engine/fifo/Makefile \
	   nvkm/engine/graph/Makefile \
	   nvkm/engine/mpeg/Makefile \
	   nvkm/engine/perfmon/Makefile \
	   nvkm/engine/ppp/Makefile \
	   nvkm/engine/software/Makefile \
	   nvkm/engine/vp/Makefile \
	   nvif/Makefile \
	   lib/Makefile \
	   bin/Makefile \
)
