#ifndef SLUS_FACING_H
#define SLUS_FACING_H

#include "common/vector.h"

#define FACING_STEP_SIZE 0x8

/* The eight facing-step rows at 0x80181B94: one s32 pair per route
 * direction, read as a whole word pair by both the game overlay
 * (src/engine/game/00) and the world overlay (src/overlays/area/area030/04). */
typedef Vec2S32 FacingStep;
ASSERT_SIZE(FacingStep, FACING_STEP_SIZE);

/* D_80181B94 */
extern const FacingStep g_FacingSteps[8];

#endif
