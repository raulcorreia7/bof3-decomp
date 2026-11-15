#ifndef OVERLAY_BMAGIC_MAGIC218_03_H
#define OVERLAY_BMAGIC_MAGIC218_03_H

/* The bmagic/magic218/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

void func_801EEDB8(void);

extern Callback D_801EF774[];
/* Per ring of func_801EF250, indexed ring - 1: the texture row its band starts at, and the band height. */
extern u8       D_801EF780[];
extern u8       D_801EF788[];
extern s8       D_801EF790[];
bool            func_801EF70C(EnemyBattler* enemy);

#endif
