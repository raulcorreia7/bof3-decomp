#ifndef OVERLAY_BMAGIC_MAGIC167_03_H
#define OVERLAY_BMAGIC_MAGIC167_03_H

/* The bmagic/magic167/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern s32 D_1F800004;

/* The spark trail depth word: the depth its rim points sit at. */
extern s32 D_1F800008;

/* The spark trail angle word; the trail reads its radius and depth words before it. */
extern s32               D_1F80000C;
extern BMagicEffectSteps D_801EEC04;
extern Callback          D_801F08B8[];

#endif
