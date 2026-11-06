#ifndef OVERLAY_BMAGIC_MAGIC101_03_H
#define OVERLAY_BMAGIC_MAGIC101_03_H

/* The bmagic/magic101/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern u8 g_BattleActiveBattler;

/* One-field views of the queued-slot record at g_BattleEffects (stride 0x78). */
extern u8 D_801EC331[];

extern u8                  D_801EC334[];
extern BattleHandlerTable5 D_801EEC04;

extern u16      D_801EFCC0[];
extern u16      D_801EFCE0[];
extern Callback D_801EFCE8[];
void            func_801EF88C(void);

void func_801EF07C(void);

#endif
