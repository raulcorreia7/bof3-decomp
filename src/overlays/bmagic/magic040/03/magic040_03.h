#ifndef OVERLAY_BMAGIC_MAGIC040_03_H
#define OVERLAY_BMAGIC_MAGIC040_03_H

/* The bmagic/magic040/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The amount Effect_CountDownTimer adds to the effect work byte 9. */
#define EFFECT_TIMER_STEP 1

typedef struct Magic040Steps {
    Callback steps[4];
} Magic040Steps;

extern Magic040Steps D_801EEC10;

void func_801EF430(void* arg0);

#endif
