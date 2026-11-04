#ifndef OVERLAY_BMAGIC_MAGIC076_03_H
#define OVERLAY_BMAGIC_MAGIC076_03_H

/* The bmagic/magic076/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"
#define EFFECT_STEP_LIMIT 1

extern Callback D_801F048C[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F04A4[];
#define BMAGIC_EFFECT_SLOTS D_801F04A4
#define BMAGIC_EFFECT_COUNT 64
void            func_800AF764(void);
void            func_801EF698(void);

#endif
