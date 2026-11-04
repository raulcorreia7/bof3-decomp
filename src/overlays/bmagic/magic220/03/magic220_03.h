#ifndef OVERLAY_BMAGIC_MAGIC220_03_H
#define OVERLAY_BMAGIC_MAGIC220_03_H

/* The bmagic/magic220/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback D_801F0700[];

extern Callback     D_801F0704[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F0710[];
#define BMAGIC_EFFECT_SLOTS D_801F0710
#define BMAGIC_EFFECT_COUNT 64
void func_801F0334(void);

#endif
