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
    if ((TASK(Actor)->direction == FACING_UP_RIGHT) || (TASK(Actor)->direction == FACING_DOWN_LEFT)) {
        step               = 0x20;
        TASK(Actor)->timer = step;
    } else {
        step               = 0x10;
        TASK(Actor)->timer = step;
    }
    TASK(Actor)->timer = (TASK(Actor)->timer / (rate & BYTE_MASK));
    if ((g_Game.flags & 0x1000) != 0) {
        TASK(Actor)->timer *= 2;
    }
    TASK(Actor)->vx = g_FacingOffsets[TASK(Actor)->direction].x * rate;
    high            = g_FacingOffsets[TASK(Actor)->direction].y * rate;
    TASK(Actor)->vy = high;
    pos_x           = TASK(Actor)->pos.x.fixed + TASK(Actor)->vx * TASK(Actor)->timer;
    pos_y           = TASK(Actor)->pos.y.fixed + high * TASK(Actor)->timer;
    result          = Area_HeightReadStep(pos_x, pos_y, TASK(Actor)->direction);
    if (SP_REF(volatile u8, 0x0u) != 0) {
        result = Area_HeightRead(pos_x, pos_y);
    }
    TASK(Actor)->vz = (result - COORD_INT(TASK(Actor)->pos.z)) / TASK(Actor)->timer;
}
