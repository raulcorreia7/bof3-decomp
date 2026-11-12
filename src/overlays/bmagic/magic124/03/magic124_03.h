#ifndef OVERLAY_BMAGIC_MAGIC124_03_H
#define OVERLAY_BMAGIC_MAGIC124_03_H

/* The bmagic/magic124/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback     D_801F08F4[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F0900[];
#define BMAGIC_EFFECT_SLOTS D_801F0900
#define BMAGIC_EFFECT_COUNT 64
void func_801EF6E8(void);
void func_801F03E0(void);
void func_801F05B4(void);

#endif
