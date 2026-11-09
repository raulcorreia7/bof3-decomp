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

/* The eight facing-step rows at 0x80181B94. */
/* D_80181B94 */
extern const Point2DL g_FacingSteps[8];

#endif
