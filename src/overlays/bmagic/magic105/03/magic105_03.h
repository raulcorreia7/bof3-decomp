#ifndef OVERLAY_BMAGIC_MAGIC105_03_H
#define OVERLAY_BMAGIC_MAGIC105_03_H

/* The bmagic/magic105/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern MagicTaskFuncs D_801EEC04;
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F00A0[];
#define BMAGIC_EFFECT_SLOTS D_801F00A0
#define BMAGIC_EFFECT_COUNT 64

#endif
