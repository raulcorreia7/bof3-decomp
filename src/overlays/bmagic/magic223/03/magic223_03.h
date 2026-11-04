#ifndef OVERLAY_BMAGIC_MAGIC223_03_H
#define OVERLAY_BMAGIC_MAGIC223_03_H

/* The bmagic/magic223/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback D_801EFC40[];

void func_801EF1E8(void);

extern Callback D_801EFC44[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801EFC60[];
#define BMAGIC_EFFECT_SLOTS D_801EFC60
#define BMAGIC_EFFECT_COUNT 64
void            func_801EF7A8(void);

#endif
