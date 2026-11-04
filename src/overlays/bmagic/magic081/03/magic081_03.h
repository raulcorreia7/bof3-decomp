#ifndef OVERLAY_BMAGIC_MAGIC081_03_H
#define OVERLAY_BMAGIC_MAGIC081_03_H

/* The bmagic/magic081/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BattleHandlerTable3 D_801EEC14;
extern MagicTaskFuncs      D_801EEC20;
extern BattleEffect*       D_801EC2E0;
/* The effect slot table BMagic_AllocEffect scans. */
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801EFA8C[];
#define BMAGIC_EFFECT_SLOTS D_801EFA8C
#define BMAGIC_EFFECT_COUNT BATTLE_EFFECT_COUNT

#endif
