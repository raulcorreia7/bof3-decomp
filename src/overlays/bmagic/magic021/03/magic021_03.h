#ifndef OVERLAY_BMAGIC_MAGIC021_03_H
#define OVERLAY_BMAGIC_MAGIC021_03_H

/* The bmagic/magic021/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern s16 D_1F800000_HALF;
extern s16 D_1F800004;

extern Callback     D_801EFE08[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801EFE14[];
#define BMAGIC_EFFECT_SLOTS D_801EFE14
#define BMAGIC_EFFECT_COUNT 64
void func_801EF7FC(void);
void func_801EF534(void);

#define MAGIC021_STEP_COUNT 3

typedef struct Magic021Steps {
    Callback steps[MAGIC021_STEP_COUNT];
} Magic021Steps;

extern Magic021Steps D_801EEC04;

extern BMagicEffectFuncs D_801EEC10;

#endif
