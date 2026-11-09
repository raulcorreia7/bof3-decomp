#ifndef OVERLAY_BMAGIC_MAGIC117_00_H
#define OVERLAY_BMAGIC_MAGIC117_00_H

/* The bmagic/magic117/00 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* Battle flag and the request hand-off these overlays toggle. */
extern Magic065SharedSteps D_801EEC04;

#define MAGIC117_STEP_COUNT 4

typedef struct Magic117Steps {
    Callback steps[MAGIC117_STEP_COUNT];
} Magic117Steps;

extern Magic117Steps D_801EEC14;

#endif
