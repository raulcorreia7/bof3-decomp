#ifndef OVERLAY_BMAGIC_MAGIC169_03_H
#define OVERLAY_BMAGIC_MAGIC169_03_H

/* The bmagic/magic169/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BmagicEffectFuncs D_801EEC14;
extern Callback          D_801F0420[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F0424[];
#define BMAGIC_EFFECT_SLOTS D_801F0424
#define BMAGIC_EFFECT_COUNT 80

#endif
