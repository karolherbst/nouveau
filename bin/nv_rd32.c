#define FMTADDR "0x%06lx"
#define FMTDATA "0x%08x"
#define NAME    "nv_rd32"
#define CAST    u32
#define READ(o) nvif_rd32(device, (o))
#define MAIN    main
#include "nv_rdfunc.h"
