#ifndef OVERLAY_BMAGIC_MAGIC008_00_H
#define OVERLAY_BMAGIC_MAGIC008_00_H

/* The bmagic/magic008/00 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* Seven step handlers: the copy at D_801EECAC reads seven words, the eighth slot is unused. */
typedef struct BMagicStepTable7 {
    Callback handlers[7];
} BMagicStepTable7;

typedef struct BMagicStepTable10 {
    Callback handlers[10];
} BMagicStepTable10;

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

extern BMagicStepTable7  D_801EECAC;
extern BMagicStepTable10 D_801EECC8;

#endif
