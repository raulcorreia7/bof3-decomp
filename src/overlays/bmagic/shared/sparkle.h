#ifndef OVERLAY_BMAGIC_SPARKLE_H
#define OVERLAY_BMAGIC_SPARKLE_H

/* The sparkle pool of magic070, magic071 and magic072. */

#include "overlays/bmagic/bmagic.h"

/* The records in the sparkle pool g_BMagicSparkles. */
#define EFFECT_SPARKLE_COUNT    128
/* Set in the header flags of a sparkle record that is in use. */
#define EFFECT_SPARKLE_IN_USE   0x01
/* The live sparkles under which the task stops waiting and fades out. */
#define EFFECT_SPARKLE_FEW_LEFT 5
/* The sparkle record being updated and its launch offset row. */
#define EFFECT_SPARKLE_TASK     g_BMagicSparkle
#define EFFECT_SPARKLE_OFFSETS  g_BMagicSparkleOffsets
/* The shortest rise of each type. */
#define EFFECT_SPARKLE_RISE     g_BMagicSparkleRises
/* The colour rows of each type. */
#define EFFECT_SPARKLE_COLORS   g_BMagicSparkleColors

/* D_801EEC04 */
extern BMagicEffectSteps  g_BMagicSparkleModes;
/* D_801EEC1C */
extern BMagicSparkleSteps g_BMagicSparkleSteps;
/* D_801F00BC: the launch offset of each sparkle row from the screen point of the battler. */
extern Pos2               g_BMagicSparkleOffsets[];
/* D_801F015C: the four colour rows of each type. */
extern u8                 g_BMagicSparkleColors[][4][3];
/* D_801F0198: the number of sparkles each type spawns. */
extern u8                 g_BMagicSparkleCounts[];
/* D_801F01A0: the launch delay between each group of four sparkles, per type. */
extern u8                 g_BMagicSparkleDelays[];
/* D_801F01A8: the shortest rise of each type. */
extern u8                 g_BMagicSparkleRises[];
/* D_801F01B4 */
extern BMagicEffect       g_BMagicSparkles[EFFECT_SPARKLE_COUNT];
/* D_801F17B4 */
extern BMagicEffect*      g_BMagicSparkle;

/* func_801EF33C */
void Effect_SparkleRunMode(void);
/* func_801F0000 */
u8   Effect_SparkleAlloc(void);

#endif
