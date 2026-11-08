#ifndef OVERLAY_BMAGIC_MAGIC138_03_H
#define OVERLAY_BMAGIC_MAGIC138_03_H

/* The bmagic/magic138/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

#define MAGIC138_STEP_COUNT 3

typedef struct Magic138Steps {
    Callback steps[MAGIC138_STEP_COUNT];
} Magic138Steps;

extern Magic138Steps D_801EEC10;

extern Magic138Steps D_801EEC1C;

#endif
