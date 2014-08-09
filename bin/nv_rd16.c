#define FMTADDR "0x%06lx"
#define FMTDATA "0x%04x"
#define NAME    "nv_rd16"
#define CAST    u16
#define READ(o) nvif_rd16(device, (o))
#define MAIN    main
#include "nv_rdfunc.h"
