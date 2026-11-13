#ifndef OVERLAY_BMAGIC_MAGIC125_03_H
#define OVERLAY_BMAGIC_MAGIC125_03_H

/* The bmagic/magic125/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback     D_801F05EC[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F0604[];
#define BMAGIC_EFFECT_SLOTS D_801F0604
#define BMAGIC_EFFECT_COUNT 64
void func_801EED04(void);
void func_801EF508(void);
void func_801EFB48(void);
void func_801EFFC8(void);
void func_801F020C(void);

#endif
