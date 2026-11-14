#include "game_00.h"

/* func_801B5AE4 */
MATCH s8 Game_FindRockAhead(s32 route_index, s32 route_flags) {
    s32 index;
    s32 route;
    s32 pos_x;
    s32 pos_y;

    index = 0;
    route = g_Task->direction_08;
    pos_x = g_Task->pos.x.fixed + g_FacingSteps[route].x;
    pos_y = g_Task->pos.y.fixed + g_FacingSteps[route].y;
    do {
        if (g_SpawnedActors[index].header.flags != 0 && g_SpawnedActors[index].type == 0x17) {
            /* FAKE: func_801BDD58 reads the row through the field actor layout. */
            if (func_801BDD58(pos_x, pos_y, COORD_INT(g_Task->pos.z), 0, (Actor*)&g_SpawnedActors[index]) & BYTE_MASK) {
                return index;
            }
        }
        index += 1;
    } while (index < 20U);
    return -1;
}
