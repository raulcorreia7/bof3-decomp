#ifndef OVERLAY_BMAGIC_MAGIC054_03_H
#define OVERLAY_BMAGIC_MAGIC054_03_H

/* The bmagic/magic054/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

typedef struct Magic054Steps {
    Callback steps[4];
} Magic054Steps;

extern Magic054Steps     D_801EEC04;
extern BMagicEffectFuncs D_801EEC14;

#endif
