#ifndef OVERLAY_BMAGIC_MAGIC123_03_H
#define OVERLAY_BMAGIC_MAGIC123_03_H

/* The bmagic/magic123/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801EFD74[];
#define BMAGIC_EFFECT_SLOTS D_801EFD74
#define BMAGIC_EFFECT_COUNT 90

extern u8 D_801EFD6C[];

void func_801EEDAC(void);
void BMagic_DispatchEffectMode(void);
void func_801EF584(void);
void func_801EF750(void);
void func_801EF9E0(void);

#endif
