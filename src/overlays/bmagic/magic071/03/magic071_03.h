#ifndef OVERLAY_BMAGIC_MAGIC071_03_H
#define OVERLAY_BMAGIC_MAGIC071_03_H

/* The bmagic/magic071/03 overlay. Only this image includes the file. */

/* The sparkle kind this image spawns: it picks the count, delay, rise and colours. */
#define EFFECT_SPARKLE_KIND 1

#include "overlays/bmagic/sparkle.h"

/* The effect ticker value below which Effect_NextStep advances the step. */
#define EFFECT_STEP_LIMIT 5

extern void (*D_801F01B0[])(void);

#endif
