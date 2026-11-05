#include "game_00.h"

MATCH s8 func_801B5AE4(s32 route_index, s32 route_flags) {
    s32 index;
    s32 route;
    s32 pos_x;
    s32 pos_y;

    index = 0;
    route = g_Task->direction_08;
    pos_x = g_Task->x.fixed + g_FacingSteps[route].x;
    pos_y = g_Task->y.fixed + g_FacingSteps[route].y;
    do {
        if (g_ActorSlots[index].flags != 0 && g_ActorSlots[index].type == 0x17) {
            /* FAKE: func_801BDD58 reads the row through the field actor layout. */
            if (func_801BDD58(pos_x, pos_y, COORD_INT(g_Task->z), 0, (Actor*)&g_ActorSlots[index]) & BYTE_MASK) {
                return index;
            }
        }
        index += 1;
    } while (index < 20U);
    return -1;
}
