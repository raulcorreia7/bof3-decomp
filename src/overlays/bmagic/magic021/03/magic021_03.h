#ifndef OVERLAY_BMAGIC_MAGIC021_03_H
#define OVERLAY_BMAGIC_MAGIC021_03_H

/* The bmagic/magic021/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback D_801EFE08[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801EFE14[];
#define BMAGIC_EFFECT_SLOTS D_801EFE14
#define BMAGIC_EFFECT_COUNT 64
void            func_800AF764(void);
void            func_801EF7FC(void);
void            func_801EFA48(void);

#endif
