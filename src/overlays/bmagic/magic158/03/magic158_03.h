#ifndef OVERLAY_BMAGIC_MAGIC158_03_H
#define OVERLAY_BMAGIC_MAGIC158_03_H

/* The bmagic/magic158/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback     D_801EF788[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801EF794[];
#define BMAGIC_EFFECT_SLOTS D_801EF794
#define BMAGIC_EFFECT_COUNT 64
void func_801EF2F0(void);
void func_801EF3EC(void);

#endif
