#ifndef OVERLAY_BMAGIC_MAGIC070_03_H
#define OVERLAY_BMAGIC_MAGIC070_03_H

/* The bmagic/magic070/03 overlay (Absorb, Heal). Only this image includes the file. */

/* The sparkle type this image spawns. */
#define EFFECT_SPARKLE_TYPE BMAGIC_SPARKLE_HEAL

#include "overlays/bmagic/shared/sparkle.h"

/* D_801F01B0 */
extern void (*g_BMagicSparkleRecordModes[])(void);

#endif
