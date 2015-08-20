#define FMTADDR    "0x%06llx"
#define FMTDATA    "0x%04x"
#define NAME       "nv_wr16"
#define CAST       u16
#define WRITE(o,v) nvif_wr16(&device->object, (o), (v))
#define MAIN       main
#include "nv_wrfunc.h"
