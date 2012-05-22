#define FMTADDR    "0x%06lx"
#define FMTDATA    "0x%02x"
#define NAME       "nv_wr08"
#define CAST       u8
#define WRITE(o,v) nv_wo08(device, (o), (v))
#define MAIN       main
#include "nv_wrfunc.h"
