#define FMTADDR    "0x%06llx"
#define FMTDATA    "0x%08x"
#define NAME       "nv_wr32"
#define CAST       u32
#define WRITE(o,v) nvif_wr32(&device->object, (o), (v))
#define MAIN       main
#include "nv_wrfunc.h"
