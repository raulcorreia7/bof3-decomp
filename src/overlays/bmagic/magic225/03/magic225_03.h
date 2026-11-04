#ifndef OVERLAY_BMAGIC_MAGIC225_03_H
#define OVERLAY_BMAGIC_MAGIC225_03_H

/* The bmagic/magic225/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback     D_801F03AC[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F03BC[];
#define BMAGIC_EFFECT_SLOTS D_801F03BC
#define BMAGIC_EFFECT_COUNT 32

#endif
