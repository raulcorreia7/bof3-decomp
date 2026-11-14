#ifndef SLUS_FACING_H
#define SLUS_FACING_H

#include "common/vector.h"

/* The eight-way facing code: a row of g_FacingSteps, the x/y step the facing walks. */
typedef enum Facing {
    FACING_UP_LEFT    = 0,
    FACING_UP         = 1,
    FACING_UP_RIGHT   = 2,
    FACING_RIGHT      = 3,
    FACING_DOWN_RIGHT = 4,
    FACING_DOWN       = 5,
    FACING_DOWN_LEFT  = 6,
    FACING_LEFT       = 7,
} Facing;

/* The eight facing-step rows at 0x80181B94: one s32 pair per route
 * direction, read as a whole word pair by both the game overlay
 * (src/engine/game/00) and the world overlay (src/overlays/area/area030/04). */
/* D_80181B94 */
extern const Point2l g_FacingSteps[8];

#endif
