#ifndef OVERLAY_BMAGIC_MAGIC059_03_H
#define OVERLAY_BMAGIC_MAGIC059_03_H

/* The bmagic/magic059/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The orbit angle cell the effect path keeps in the scratchpad. */
extern volatile s16 D_1F80000E;

extern u16 D_80036C00[256];
extern u16 g_BattleEffectPalette[256];

/* The facing lookup that seeds the actor's effect timer. */
extern u32      D_801F065C[4];
extern Callback D_801F0670[];
extern Callback D_801F0684[];

/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F0694[];
#define BMAGIC_EFFECT_SLOTS D_801F0694
#define BMAGIC_EFFECT_COUNT 24
void func_801EED0C(void);
void func_801EF118(void);
void func_801EF638(void);
void func_801EFE48(void);
void func_801F01A4(void);
void func_801EF70C(s32 phase, s32 radius);

#endif
