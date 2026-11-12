#ifndef OVERLAY_BMAGIC_MAGIC168_03_H
#define OVERLAY_BMAGIC_MAGIC168_03_H

/* The bmagic/magic168/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

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
/* The colour rows of each kind. */
#define EFFECT_SPARKLE_COLORS D_801F0158
extern u8 D_801F0158[][4][3];

extern BMagicEffectWorkSteps D_801EEC1C;
extern BMagicEffectFuncs     D_801EEC04;
void                         func_801EF338(void);

/* The sparkle record being updated, its launch offset row and the shortest rise per kind. */
#define EFFECT_SPARKLE_TASK    D_801F17B0
#define EFFECT_SPARKLE_OFFSETS D_801F00B8
#define EFFECT_SPARKLE_RISE    D_801F01A4
extern Point2D D_801F00B8[];
extern u8      D_801F01A4[];

#endif
