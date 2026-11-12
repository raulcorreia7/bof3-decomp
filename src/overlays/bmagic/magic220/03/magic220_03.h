#ifndef OVERLAY_BMAGIC_MAGIC220_03_H
#define OVERLAY_BMAGIC_MAGIC220_03_H

/* The bmagic/magic220/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern s16 D_1F800004;

extern Callback D_801F06E0[];
extern Callback D_801F0700[];

extern Callback     D_801F0704[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F0710[];
#define BMAGIC_EFFECT_SLOTS     D_801F0710
#define BMAGIC_EFFECT_COUNT     64
#define BMAGIC_EFFECT_SLOT_STEP func_801EFF60
extern Magic220SharedSteps D_801EEC04;
void                       func_801EFF60(void);
void                       func_801F0334(void);

#endif
