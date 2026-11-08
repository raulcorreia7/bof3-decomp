#ifndef OVERLAY_BMAGIC_MAGIC020_03_H
#define OVERLAY_BMAGIC_MAGIC020_03_H

/* The bmagic/magic020/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BMagicEffectFuncs D_801EEC04;

typedef struct Magic020Steps801EEC3C {
    Callback steps[3];
} Magic020Steps801EEC3C;

typedef struct Magic020Steps801EEC1C {
    Callback steps[8];
} Magic020Steps801EEC1C;

extern Magic020Steps801EEC3C D_801EEC3C;
extern Magic020Steps801EEC1C D_801EEC1C;

void func_801EFD88(void);

#endif
