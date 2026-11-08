#ifndef OVERLAY_BMAGIC_MAGIC052_03_H
#define OVERLAY_BMAGIC_MAGIC052_03_H

/* The bmagic/magic052/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

#define MAGIC052_STEP_COUNT 3

typedef struct Magic052Steps {
    Callback steps[MAGIC052_STEP_COUNT];
} Magic052Steps;

extern Magic052Steps D_801EEC10;

#endif
