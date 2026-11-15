#ifndef OVERLAY_BMAGIC_MAGIC006_03_H
#define OVERLAY_BMAGIC_MAGIC006_03_H

/* The bmagic/magic006/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BMagicEffectFuncs D_801EEC04;

extern s16 D_1F800008;
/* The outer radius of each blade func_801EF478 draws, indexed by half its angle step. */
extern s16 D_801F0A30[];

#define MAGIC006_STEP_COUNT 3

typedef struct Magic006Steps {
    Callback steps[MAGIC006_STEP_COUNT];
} Magic006Steps;

#define MAGIC006_SECOND_STEP_COUNT 4

typedef struct Magic006SecondSteps {
    Callback steps[MAGIC006_SECOND_STEP_COUNT];
} Magic006SecondSteps;

extern Magic006Steps D_801EEC1C;

extern Magic006SecondSteps D_801EEC28;

void func_801EEC90(void);

void func_800AF3A0(VECTOR pos, s16 step);

void           func_801F0308(void);
extern SVECTOR D_1F800014[];
void           func_801F0790(void);

#endif
