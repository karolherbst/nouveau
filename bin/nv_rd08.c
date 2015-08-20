#define FMTADDR "0x%06llx"
#define FMTDATA "0x%02x"
#define NAME    "nv_rd08"
#define CAST    u8
#define READ(o) nvif_rd08(&device->object, (o))
#define MAIN    main
#include "nv_rdfunc.h"
