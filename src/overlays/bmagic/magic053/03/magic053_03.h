#ifndef OVERLAY_BMAGIC_MAGIC053_03_H
#define OVERLAY_BMAGIC_MAGIC053_03_H

/* The bmagic/magic053/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback     D_801F056C[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F0578[];
#define BMAGIC_EFFECT_SLOTS D_801F0578
#define BMAGIC_EFFECT_COUNT 32
void func_801F01C0(void);

#endif
