#ifndef OVERLAY_BMAGIC_MAGIC039_03_H
#define OVERLAY_BMAGIC_MAGIC039_03_H

/* The bmagic/magic039/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The amount Effect_CountDownTimer adds to the effect work byte 9. */
#define EFFECT_TIMER_STEP   8

#define MAGIC039_STEP_COUNT 3

typedef struct Magic039Steps {
    Callback steps[MAGIC039_STEP_COUNT];
} Magic039Steps;

extern Magic039Steps     D_801EEC28;
extern BMagicEffectFuncs D_801EEC10;

void func_801EF758(void);

#endif
