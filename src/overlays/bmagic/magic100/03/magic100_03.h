#ifndef OVERLAY_BMAGIC_MAGIC100_03_H
#define OVERLAY_BMAGIC_MAGIC100_03_H

/* The bmagic/magic100/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The step handlers the module runner dispatches. */
extern Callback D_801EFDD0[];

/* One-field views of the queued-slot record at g_BattleEffects (stride 0x78). */
extern u8 D_801EC331[];
extern u8 D_801EC33B[];

void func_801EF434(void);
void func_801EF4E8(void);
void func_801EF8E8(void);
void func_801EF9D4(void);

#endif
