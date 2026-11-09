#ifndef OVERLAY_BMAGIC_MAGIC054_03_H
#define OVERLAY_BMAGIC_MAGIC054_03_H

/* The bmagic/magic054/03 overlay. */

#include "overlays/bmagic/bmagic.h"

#define MAGIC054_STEP_COUNT 4

typedef struct Magic054Steps {
    Callback steps[MAGIC054_STEP_COUNT];
} Magic054Steps;

extern Magic054Steps     D_801EEC04;
extern BMagicEffectFuncs D_801EEC14;

#endif
