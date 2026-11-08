#ifndef OVERLAY_BMAGIC_MAGIC096_03_H
#define OVERLAY_BMAGIC_MAGIC096_03_H

/* The bmagic/magic096/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

typedef struct Magic096Steps {
    Callback steps[5];
} Magic096Steps;

extern Magic096Steps D_801EEC10;
extern u8            D_801F0488[];

#endif
