#ifndef OVERLAY_BMAGIC_MAGIC017_03_H
#define OVERLAY_BMAGIC_MAGIC017_03_H

/* The bmagic/magic017/03 overlay. */

#include "overlays/bmagic/bmagic.h"

#define MAGIC017_STEP_COUNT 10

typedef struct Magic017Steps {
    Callback handlers[MAGIC017_STEP_COUNT];
} Magic017Steps;

extern Magic017Steps D_801EEC10;

#endif
