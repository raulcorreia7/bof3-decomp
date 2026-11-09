#ifndef OVERLAY_BMAGIC_MAGIC057_03_H
#define OVERLAY_BMAGIC_MAGIC057_03_H

/* The bmagic/magic057/03 overlay. */

#include "overlays/bmagic/bmagic.h"

extern BattleEffect* volatile D_801EC2E0;

#define MAGIC057_STEP_COUNT 4

typedef struct Magic057Steps {
    Callback steps[MAGIC057_STEP_COUNT];
} Magic057Steps;

#define MAGIC057_SECOND_STEP_COUNT 3

typedef struct Magic057SecondSteps {
    Callback steps[MAGIC057_SECOND_STEP_COUNT];
} Magic057SecondSteps;

extern Magic057Steps       D_801EEC10;
extern Magic057SecondSteps D_801EEC20;

extern Magic057SecondSteps D_801EEC2C;

extern Magic057SecondSteps D_801EEC38;

extern Magic057SecondSteps D_801EEC44;

extern u8 D_801EFADC[];
#endif
