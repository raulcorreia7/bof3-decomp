#ifndef OVERLAY_BMAGIC_MAGIC168_03_H
#define OVERLAY_BMAGIC_MAGIC168_03_H

/* The bmagic/magic168/03 overlay (Cure). Only this image includes the file. */

/* The sparkle type this image spawns. */
#define EFFECT_SPARKLE_TYPE BMAGIC_SPARKLE_CURE

#include "overlays/bmagic/shared/sparkle.h"

/* The effect slot table BMagic_AllocEffect scans, and its row count. */
#define BMAGIC_EFFECT_SLOTS g_BMagicSparkles
#define BMAGIC_EFFECT_COUNT EFFECT_SPARKLE_COUNT

#endif
