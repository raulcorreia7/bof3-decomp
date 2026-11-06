#ifndef SLUS_FACING_H
#define SLUS_FACING_H

#include "common/vector.h"

/* The eight-way facing code: a row of g_FacingSteps, the x/y step the facing walks. */
typedef enum Facing {
    FACING_NW = 0,
    FACING_N  = 1,
    FACING_NE = 2,
    FACING_E  = 3,
    FACING_SE = 4,
    FACING_S  = 5,
    FACING_SW = 6,
    FACING_W  = 7,
} Facing;

/* The eight facing-step rows at 0x80181B94: one s32 pair per route
 * direction, read as a whole word pair by both the game overlay
 * (src/engine/game/00) and the world overlay (src/overlays/area/area030/04). */
/* D_80181B94 */
extern const Point2DL g_FacingSteps[8];

#endif
