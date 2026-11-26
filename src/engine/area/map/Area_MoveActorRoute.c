#include "engine/game/00/game_00.h"

/* func_801ABBA8 */
MATCH void Area_MoveActorRoute(void* sub, s32 route) {
    u8  rate;
    u8  masked;
    u8  slot;
    s32 high;
    s32 pos_x;
    s32 pos_y;
    s16 result;

    masked = route & BYTE_MASK;
    slot   = route & BYTE_MASK;
    rate   = g_RouteSpeedScale[((u8*)sub)[4]];
    if ((masked == 2) || (masked == 6)) {
        SELF(Actor)->timer = 32;
    } else {
        SELF(Actor)->timer = 16;
    }
    SELF(Actor)->timer = (SELF(Actor)->timer / (rate & BYTE_MASK));
    SELF(Actor)->vx    = g_FacingOffsets[slot].x * rate;
    high               = g_FacingOffsets[slot].y * rate;
    SELF(Actor)->vy    = high;
    pos_x              = SELF(Actor)->pos.x.fixed + SELF(Actor)->vx * SELF(Actor)->timer;
    pos_y              = SELF(Actor)->pos.y.fixed + high * SELF(Actor)->timer;
    if ((((u8*)sub)[0] & 0x80) == 0) {
        result = Area_HeightGet(pos_x, pos_y, slot);
        if (SP_REF(volatile u8, 0x0u) != 0) {
            result = Area_HeightSample(pos_x, pos_y);
        }
        SELF(Actor)->vz = (result - COORD_INT(SELF(Actor)->pos.z)) / SELF(Actor)->timer;
    }
    SELF(Actor)->header.flags |= ACTOR_FLAG_STEP_MOVE;
}
