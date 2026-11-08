#ifndef OVERLAY_BMAGIC_MAGIC161_03_H
#define OVERLAY_BMAGIC_MAGIC161_03_H

/* The bmagic/magic161/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

#define MAGIC161_STEP_COUNT 5

typedef struct Magic161Steps {
    Callback steps[MAGIC161_STEP_COUNT];
} Magic161Steps;

extern Magic161Steps D_801EEC10;

void func_801EF1DC(void);

#endif
