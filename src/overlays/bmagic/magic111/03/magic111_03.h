#ifndef OVERLAY_BMAGIC_MAGIC111_03_H
#define OVERLAY_BMAGIC_MAGIC111_03_H

/* The bmagic/magic111/03 overlay. */

#include "overlays/bmagic/bmagic.h"

extern Callback D_801EFAA8[];

#define MAGIC111_STEP_COUNT 3

typedef struct Magic111Steps {
    Callback steps[MAGIC111_STEP_COUNT];
} Magic111Steps;

extern Magic111Steps D_801EEC10;

extern Callback D_801EFAB8[];

#endif
