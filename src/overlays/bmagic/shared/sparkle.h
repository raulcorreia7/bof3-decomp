#ifndef OVERLAY_BMAGIC_SPARKLE_H
#define OVERLAY_BMAGIC_SPARKLE_H

/* The sparkle pool of magic070, magic071 and magic072. */

#include "overlays/bmagic/bmagic.h"

/* The records in the sparkle pool D_801F01B4. */
#define EFFECT_SPARKLE_COUNT   128
/* Set in the header flags of a sparkle record that is in use. */
#define EFFECT_SPARKLE_IN_USE  0x01
/* The launch offset table D_801F00BC. */
/* The sparkle record being updated and its launch offset row. */
#define EFFECT_SPARKLE_TASK    D_801F17B4
#define EFFECT_SPARKLE_OFFSETS D_801F00BC
/* The shortest rise of each type. */
#define EFFECT_SPARKLE_RISE    D_801F01A8
/* The colour rows of each type. */
#define EFFECT_SPARKLE_COLORS  D_801F015C

extern BMagicEffectSteps  D_801EEC04;
extern BMagicSparkleSteps D_801EEC1C;
/* The launch offset of each sparkle row from the screen point of the battler. */
extern Pos2               D_801F00BC[];
/* The four colour rows of each type. */
extern u8                 D_801F015C[][4][3];
/* The number of sparkles each type spawns. */
extern u8                 D_801F0198[];
/* The launch delay between each group of four sparkles, per type. */
extern u8                 D_801F01A0[];
/* The shortest rise of each type. */
extern u8                 D_801F01A8[];
extern BMagicEffect       D_801F01B4[EFFECT_SPARKLE_COUNT];

void func_801EF33C(void);
u8   func_801F0000(void);

#endif
