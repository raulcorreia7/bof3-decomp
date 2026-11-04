#ifndef OVERLAY_BMAGIC_MAGIC013_03_H
#define OVERLAY_BMAGIC_MAGIC013_03_H

/* The bmagic/magic013/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback     D_801F03C0[];
extern Callback     D_801F03DC[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F03E4[];
#define BMAGIC_EFFECT_SLOTS D_801F03E4
#define BMAGIC_EFFECT_COUNT 64
void func_801EF4F0(void);
void func_801F00A8(void);
void func_801F0164(void);
void func_801EF79C(void);
void func_801EF648(void);
void func_801EFAA8(void);

#endif
