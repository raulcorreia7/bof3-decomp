#ifndef OVERLAY_BMAGIC_MAGIC161_03_H
#define OVERLAY_BMAGIC_MAGIC161_03_H

/* The bmagic/magic161/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

typedef struct Magic161Steps {
    Callback steps[5];
} Magic161Steps;

extern Magic161Steps D_801EEC10;

void func_801EF1DC(void);

#endif
