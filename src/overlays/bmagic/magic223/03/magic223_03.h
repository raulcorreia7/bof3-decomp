#ifndef OVERLAY_BMAGIC_MAGIC223_03_H
#define OVERLAY_BMAGIC_MAGIC223_03_H

/* The bmagic/magic223/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback D_801EFC40[];

extern s32 D_1F800004;
/* The four facing angle offsets the wind sway adds to the phase. */
extern s32 D_801EFC50[];

void func_801EF1E8(void);

extern Callback     D_801EFC44[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801EFC60[];
#define BMAGIC_EFFECT_SLOTS     D_801EFC60
#define BMAGIC_EFFECT_COUNT     64
#define BMAGIC_EFFECT_SLOT_STEP func_801EF3C0
extern Magic220SharedSteps D_801EEC04;
void                       func_801EF3C0(void);
void                       func_801EF7A8(void);

#endif
