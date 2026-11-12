#ifndef OVERLAY_BMAGIC_MAGIC046_03_H
#define OVERLAY_BMAGIC_MAGIC046_03_H

/* The bmagic/magic046/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern SVECTOR D_1F800014[];

#define MAGIC046_STEP_COUNT 3

typedef struct Magic046Steps {
    Callback steps[MAGIC046_STEP_COUNT];
} Magic046Steps;

extern EffectDispatchSteps D_801EEC10;

extern Magic046Steps D_801EEC1C;
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect  D_801EFF3C[];
#define BMAGIC_EFFECT_SLOTS D_801EFF3C
#define BMAGIC_EFFECT_COUNT BATTLE_EFFECT_COUNT

void func_801EF7E8(void);
void func_801EFB90(void);
void func_801EFC48(void);
void func_801EED28(void);
void func_801EF324(void);

#endif
