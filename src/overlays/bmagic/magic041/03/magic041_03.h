#ifndef OVERLAY_BMAGIC_MAGIC041_03_H
#define OVERLAY_BMAGIC_MAGIC041_03_H

/* The bmagic/magic041/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BMagicEffectFuncs D_801EEC04;

typedef struct Magic041Steps801EEC1C {
    Callback steps[3];
} Magic041Steps801EEC1C;

typedef struct Magic041Steps801EEC28 {
    Callback steps[4];
} Magic041Steps801EEC28;

extern Magic041Steps801EEC1C D_801EEC1C;

extern Magic041Steps801EEC28 D_801EEC28;

void func_801EF670(void);

#endif
