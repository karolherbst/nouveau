#define FMTADDR    "0x%06llx"
#define FMTDATA    "0x%02x"
#define NAME       "nv_wr08"
#define CAST       u8
#define WRITE(o,v) nvif_wr08(device, (o), (v))
#define MAIN       main
#include "nv_wrfunc.h"
