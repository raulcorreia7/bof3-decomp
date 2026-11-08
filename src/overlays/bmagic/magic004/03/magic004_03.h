#ifndef OVERLAY_BMAGIC_MAGIC004_03_H
#define OVERLAY_BMAGIC_MAGIC004_03_H

/* The bmagic/magic004/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Func801EEC28Steps D_801EEC04;

typedef struct Magic004Steps {
    Callback steps[4];
} Magic004Steps;

extern Magic004Steps D_801EEC18;
extern u16           D_801EFE40[];

#endif
