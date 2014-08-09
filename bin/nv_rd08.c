#define FMTADDR "0x%06lx"
#define FMTDATA "0x%02x"
#define NAME    "nv_rd08"
#define CAST    u8
#define READ(o) nvif_rd08(device, (o))
#define MAIN    main
#include "nv_rdfunc.h"
