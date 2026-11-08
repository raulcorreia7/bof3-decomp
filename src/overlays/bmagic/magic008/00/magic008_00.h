#ifndef OVERLAY_BMAGIC_MAGIC008_00_H
#define OVERLAY_BMAGIC_MAGIC008_00_H

/* The bmagic/magic008/00 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

#define MAGIC008_EARLY_STEP_COUNT 7
#define MAGIC008_STEP_COUNT       10

typedef struct Magic008EarlySteps {
    Callback handlers[MAGIC008_EARLY_STEP_COUNT];
} Magic008EarlySteps;

typedef struct Magic008Steps {
    Callback handlers[MAGIC008_STEP_COUNT];
} Magic008Steps;

extern EffectStepFuncs4  D_801EEC04;
extern BMagicEffectFuncs D_801EEC58;

extern EffectStepFuncs3  D_801EEC14;
extern EffectStepFuncs5  D_801EEC70;
extern EffectStepFuncs4  D_801EEC20;
extern EffectStepFuncs4  D_801EEC30;
extern EffectStepFuncs3  D_801EEC40;
extern EffectStepFuncs3  D_801EEC4C;
extern EffectStepFuncs4  D_801EEC84;
extern BMagicEffectFuncs D_801EEC94;

extern Magic008EarlySteps D_801EECAC;
extern Magic008Steps      D_801EECC8;

#endif
