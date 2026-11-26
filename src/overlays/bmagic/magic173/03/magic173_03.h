#ifndef OVERLAY_BMAGIC_MAGIC173_03_H
#define OVERLAY_BMAGIC_MAGIC173_03_H

/* The bmagic/magic173/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The counter (byte 0x09) drops by 4 per frame. */
#define EFFECT_TIMER_TICK 4
/* D_801F0990 */
extern Callback g_BMagicIntimidateStreakSteps[];
/* D_801F09A0 */
extern Callback g_BMagicIntimidateImpactSteps[];

/* D_801F09B0 */
extern BMagicTrailPoint BMagic_Trail[][BMAGIC_TRAIL_LENGTH];

/* func_800AF3A0 */
void Battle_StepRangeToward(VECTOR pos, s16 step);
/* func_801EEC5C */
void BMagic_IntimidateInit(void);
/* func_801EF4EC */
void BMagic_IntimidateDrawStreakNarrow(void);
/* func_801EFA34 */
void BMagic_IntimidateDrawStreakWide(void);
/* func_801F02B0 */
/* func_801F03A0 */
/* func_801F075C */
void BMagic_IntimidateDrawImpactBurst(void);

#endif
