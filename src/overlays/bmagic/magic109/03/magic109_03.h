#ifndef OVERLAY_BMAGIC_MAGIC109_03_H
#define OVERLAY_BMAGIC_MAGIC109_03_H

/* The bmagic/magic109/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Magic010SharedSteps D_801EEC04;

void func_801EF0F8(s32 offset);

/* The screen point the effect starts from, by g_Battle.scroll_dir. */
extern Offset2 D_801EF9D8[];

/* Three tables of 16 points; func_801EF0F8 writes and reads each point pair. */
extern Offset2 D_801EF9F8[16];
extern Offset2 D_801EFA78[16];
extern Offset2 D_801EFAF8[16];

#endif
