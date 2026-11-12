#ifndef OVERLAY_BMAGIC_MAGIC072_03_H
#define OVERLAY_BMAGIC_MAGIC072_03_H

/* The bmagic/magic072/03 overlay. Only this image includes the file. */

/* The sparkle kind this image spawns: it picks the count, delay, rise and colours. */
#define EFFECT_SPARKLE_KIND 2

#include "overlays/bmagic/sparkle.h"

/* The work record whose rays this image draws. */
#define EFFECT_DRAW_WORK D_801F17B4

extern void (*D_801F01B0[])(void);

#endif
