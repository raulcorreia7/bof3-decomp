#ifndef OVERLAY_BMAGIC_MAGIC168_03_H
#define OVERLAY_BMAGIC_MAGIC168_03_H

/* The bmagic/magic168/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The effect ticker value below which Effect_NextStep advances the step. */
#define EFFECT_STEP_LIMIT 5

extern void (*D_801F01AC[])(void);

/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BMagicEffectWork D_801F01B0[];
#define BMAGIC_EFFECT_SLOTS D_801F01B0
#define BMAGIC_EFFECT_COUNT 128

/* The sparkle kind this image spawns: it picks the count and the launch delay. */
#define EFFECT_SPARKLE_KIND 3

/* The number of sparkles each kind spawns. */
extern u8 D_801F0194[];
/* The launch delay between each group of four sparkles, per kind. */
extern u8 D_801F019C[];

u32                        BMagic_AllocEffect(void);
extern BattleHandlerTable3 D_801EEC1C;
void                       func_801EFCD8(void);
void                       func_801EF80C(u16 angle, u16 radius);
void                       func_801EFA40(u16 angle, u16 radius);
extern BMagicEffectFuncs   D_801EEC04;
void                       func_801EF338(void);

#endif
