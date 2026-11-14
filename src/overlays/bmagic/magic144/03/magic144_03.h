#ifndef OVERLAY_BMAGIC_MAGIC144_03_H
#define OVERLAY_BMAGIC_MAGIC144_03_H

/* The bmagic/magic144/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"
#define MAGIC092_STEP_X 16
#define MAGIC092_RISE_Y 12

extern SVECTOR  D_1F800014[];
extern Callback D_801F04D4[];
extern Callback D_801F04FC[];

extern Callback D_801F04E4[];
void            func_801EF818(void);

extern Callback     D_801F04EC[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F050C[];
#define BMAGIC_EFFECT_SLOTS D_801F050C
#define BMAGIC_EFFECT_COUNT BATTLE_EFFECT_COUNT
void func_801EF294(void);
void func_801EED04(void);
void func_801EF510(void);

void func_801F01D0(void);

#endif
