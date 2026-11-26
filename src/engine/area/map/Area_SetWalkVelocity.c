#include "engine/game/00/game_00.h"

/* func_801C2538 */
MATCH void Area_SetWalkVelocity(void) {
    u8  rate;
    u32 step;
    s32 high;
    s32 pos_x;
    s32 pos_y;
    s16 result;

    /* Step size from route type; rate from the shared selector bundle. */
    rate = g_RouteSpeedScale[g_Game.current->u.field.counter.unsigned_value];
    if ((SELF(Actor)->direction == FACING_UP_RIGHT) || (SELF(Actor)->direction == FACING_DOWN_LEFT)) {
        step               = 0x20;
        SELF(Actor)->timer = step;
    } else {
        step               = 0x10;
        SELF(Actor)->timer = step;
    }
    SELF(Actor)->timer = (SELF(Actor)->timer / (rate & BYTE_MASK));
    if ((g_Game.flags & 0x1000) != 0) {
        SELF(Actor)->timer *= 2;
    }
    SELF(Actor)->vx = g_FacingOffsets[SELF(Actor)->direction].x * rate;
    high            = g_FacingOffsets[SELF(Actor)->direction].y * rate;
    SELF(Actor)->vy = high;
    pos_x           = SELF(Actor)->pos.x.fixed + SELF(Actor)->vx * SELF(Actor)->timer;
    pos_y           = SELF(Actor)->pos.y.fixed + high * SELF(Actor)->timer;
    result          = Area_HeightReadStep(pos_x, pos_y, SELF(Actor)->direction);
    if (SP_REF(volatile u8, 0x0u) != 0) {
        result = Area_HeightRead(pos_x, pos_y);
    }
    SELF(Actor)->vz = (result - COORD_INT(SELF(Actor)->pos.z)) / SELF(Actor)->timer;
}
