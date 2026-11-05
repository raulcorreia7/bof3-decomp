#ifndef OVERLAY_BMAGIC_MAGIC058_03_H
#define OVERLAY_BMAGIC_MAGIC058_03_H

/* The bmagic/magic058/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BattleHandlerTable3 D_801EEC1C;

extern BattleHandlerTable3 D_801EEC10;
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect        D_801EFEF4[];
extern u8                  D_801EC2E4;
#define BMAGIC_EFFECT_SLOTS D_801EFEF4
#define BMAGIC_EFFECT_COUNT 36

#endif
