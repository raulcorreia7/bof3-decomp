#ifndef OVERLAY_BMAGIC_MAGIC093_03_H
#define OVERLAY_BMAGIC_MAGIC093_03_H

/* The bmagic/magic093/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback D_801F08C4[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F08D4[];
#define BMAGIC_EFFECT_SLOTS D_801F08D4
#define BMAGIC_EFFECT_COUNT 32
void            func_800AF764(void);
void            func_801F01F0(void);

#endif
