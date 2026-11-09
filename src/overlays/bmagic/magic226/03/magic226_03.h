#ifndef OVERLAY_BMAGIC_MAGIC226_03_H
#define OVERLAY_BMAGIC_MAGIC226_03_H

/* The bmagic/magic226/03 overlay. */

#include "overlays/bmagic/bmagic.h"

extern Callback D_801F0C44[];
extern Callback D_801F0C60[];

extern Callback D_801F0C78[];
void            func_801F01B8(void);

extern Callback     D_801F0C84[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F0C90[];
#define BMAGIC_EFFECT_SLOTS     D_801F0C90
#define BMAGIC_EFFECT_COUNT     BATTLE_EFFECT_COUNT
#define BMAGIC_EFFECT_SLOT_STEP func_801EFD84
extern Magic220SharedSteps D_801EEC04;
void                       BMagic_DrawDarkRing(void);
void                       func_801EFD84(void);
void                       func_801F07D4(void);

#endif
