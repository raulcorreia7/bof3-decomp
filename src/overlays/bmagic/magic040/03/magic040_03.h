#ifndef OVERLAY_BMAGIC_MAGIC040_03_H
#define OVERLAY_BMAGIC_MAGIC040_03_H

/* The bmagic/magic040/03 overlay. */

#include "overlays/bmagic/bmagic.h"

#define MAGIC040_STEP_COUNT 4

typedef struct Magic040Steps {
    Callback steps[MAGIC040_STEP_COUNT];
} Magic040Steps;

extern Magic040Steps D_801EEC10;

void func_801EF430(void* arg0);

#endif
