#include "engine/game/00/game_00.h"

/* func_801A1AE4 */
/* Returns whether the area cell test rejects the cells ahead or an actor or party member stands there. */
MATCH bool Actor_IsAheadBlocked(Actor* arg) {
    u8  route;
    s32 pos_x;
    s32 pos_y;
    s32 x;
    s32 y;

    route = arg->direction & 0x7;
    pos_x = arg->pos.x.fixed + g_FacingSteps[route].x;
    x     = pos_x;
    pos_y = arg->pos.y.fixed + g_FacingSteps[route].y;
    y     = pos_y;

    if ((func_801A1BC0(arg) & BYTE_MASK) != 0u) {
        return 1;
    }

    if (Actor_FindInRange(pos_x, pos_y, SELF(Actor)->voice_flags.scene_flag) == -1) {
        return Game_GetPartySize(x, y, SELF(Actor)->voice_flags.scene_flag) != -1;
    }

    return 1;
}
