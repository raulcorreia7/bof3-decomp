#ifndef OVERLAY_BMAGIC_MAGIC076_03_H
#define OVERLAY_BMAGIC_MAGIC076_03_H

/* The bmagic/magic076/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback     D_801F048C[];
/* The number of effects each kind spawns. */
extern u8           D_801F049C[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F04A4[];
extern s16          D_1F800004;
#define BMAGIC_EFFECT_SLOTS D_801F04A4
#define BMAGIC_EFFECT_COUNT 64

void func_801EF698(void);

#endif
