#define FMTADDR    "0x%06lx"
#define FMTDATA    "0x%04x"
#define NAME       "nv_wr16"
#define CAST       u16
#define WRITE(o,v) nv_wo16(device, (o), (v))
#define MAIN       main
#include "nv_wrfunc.h"
