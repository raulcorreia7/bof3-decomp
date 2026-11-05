#ifndef OVERLAY_BMAGIC_MAGIC102_03_H
#define OVERLAY_BMAGIC_MAGIC102_03_H

/* The bmagic/magic102/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern MagicTaskFuncs D_801EEC04;

/* This effect steps the shared tick counter (word_08.byte.unk_09) by one per
 * step and advances the magic step at its limit. */
#define EFFECT_TICK_INCREMENT 1
#define EFFECT_TICK_LIMIT     0x10

#endif
