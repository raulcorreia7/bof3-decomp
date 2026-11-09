#ifndef OVERLAY_BMAGIC_MAGIC154_03_H
#define OVERLAY_BMAGIC_MAGIC154_03_H

/* The bmagic/magic154/03 overlay. */

#include "overlays/bmagic/bmagic.h"

extern Magic065SharedSteps D_801EEC04;

#define MAGIC154_STEP_COUNT 4

typedef struct Magic154Steps {
    Callback steps[MAGIC154_STEP_COUNT];
} Magic154Steps;

extern Magic154Steps D_801EEC14;

#endif
