#ifndef OVERLAY_BMAGIC_MAGIC041_03_H
#define OVERLAY_BMAGIC_MAGIC041_03_H

/* The bmagic/magic041/03 overlay. */

#include "overlays/bmagic/bmagic.h"

extern BMagicEffectFuncs D_801EEC04;

#define MAGIC041_STEP_COUNT 3

typedef struct Magic041Steps {
    Callback steps[MAGIC041_STEP_COUNT];
} Magic041Steps;

#define MAGIC041_SECOND_STEP_COUNT 4

typedef struct Magic041SecondSteps {
    Callback steps[MAGIC041_SECOND_STEP_COUNT];
} Magic041SecondSteps;

extern Magic041Steps D_801EEC1C;

extern Magic041SecondSteps D_801EEC28;

void func_801EF670(void);

#endif
