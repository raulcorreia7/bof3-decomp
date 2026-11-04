#ifndef OVERLAY_BMAGIC_MAGIC213_03_H
#define OVERLAY_BMAGIC_MAGIC213_03_H

/* The bmagic/magic213/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback     D_801EF8A4[];
extern Callback     D_801EF8B4[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801EF8C0[];
#define BMAGIC_EFFECT_SLOTS D_801EF8C0
#define BMAGIC_EFFECT_COUNT 64

#endif
