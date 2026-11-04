#ifndef OVERLAY_BMAGIC_MAGIC043_03_H
#define OVERLAY_BMAGIC_MAGIC043_03_H

/* The bmagic/magic043/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback     D_801EFC8C[];
extern u16          D_801EFC9C[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801EFCA4[];
#define BMAGIC_EFFECT_SLOTS D_801EFCA4
#define BMAGIC_EFFECT_COUNT 64
void func_801EF72C(void);
void func_801EF7F8(void);

#endif
