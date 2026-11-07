#ifndef OVERLAY_BMAGIC_MAGIC168_03_H
#define OVERLAY_BMAGIC_MAGIC168_03_H

/* The bmagic/magic168/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The effect ticker value below which Effect_NextStep advances the step. */
#define EFFECT_STEP_LIMIT 5

extern void (*D_801F01AC[])(void);

/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BMagicEffectWork D_801F01B0[];
#define BMAGIC_EFFECT_SLOTS D_801F01B0
#define BMAGIC_EFFECT_COUNT 128

#endif
