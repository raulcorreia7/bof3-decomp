#ifndef OVERLAY_BMAGIC_MAGIC166_03_H
#define OVERLAY_BMAGIC_MAGIC166_03_H

/* The bmagic/magic166/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback D_801EF71C[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801EF724[];
#define BMAGIC_EFFECT_SLOTS D_801EF724
#define BMAGIC_EFFECT_COUNT 64
void            func_801EF284(void);
void            func_801EF380(void);

#endif
