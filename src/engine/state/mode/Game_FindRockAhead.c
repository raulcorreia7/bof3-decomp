#include "engine/game/00/game_00.h"

/* func_801B5AE4 */
MATCH s8 Game_FindRockAhead(s32 route_index, s32 route_flags) {
    s32 index;
    s32 route;
    s32 pos_x;
    s32 pos_y;

    index = 0;
    route = TASK(Actor)->direction;
    pos_x = TASK(Actor)->pos.x.fixed + g_FacingSteps[route].x;
    pos_y = TASK(Actor)->pos.y.fixed + g_FacingSteps[route].y;
    do {
        if (g_SpawnedActors[index].header.flags != 0 && g_SpawnedActors[index].type == ACTOR_TYPE_ROCK) {
            /* FAKE: Actor_IsInRange reads the row through the field actor layout. */
            if (Actor_IsInRange(pos_x, pos_y, COORD_INT(TASK(Actor)->pos.z), 0, (Actor*)&g_SpawnedActors[index]) & BYTE_MASK) {
                return index;
            }
        }
        index += 1;
    } while (index < 20U);
    return -1;
}
