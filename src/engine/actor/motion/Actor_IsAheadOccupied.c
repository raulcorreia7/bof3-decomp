#include "engine/game/00/game_00.h"

/* func_801A3AC8 */
/* Returns whether another actor or a party member stands on the cell ahead. */
MATCH bool Actor_IsAheadOccupied(Actor* record) {
    Actor* rec;
    u8     route;
    s32    x;
    s32    y;
    s32    pos_x;
    s32    pos_y;

    rec   = record;
    route = rec->direction & 0x7;
    pos_x = rec->pos.x.fixed + g_FacingSteps[route].x;
    x     = pos_x;
    pos_y = rec->pos.y.fixed + g_FacingSteps[route].y;
    y     = pos_y;
    if (Actor_FindInRange(x, y, TASK(Actor)->voice_flags.scene_flag) == -1) {
        return Game_GetPartySize(x, y, TASK(Actor)->voice_flags.scene_flag) != -1;
    }
    return 1;
}
