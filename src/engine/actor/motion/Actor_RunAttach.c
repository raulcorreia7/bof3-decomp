#include "engine/game/00/game_00.h"

/* func_801A3410 */
/* Mode 7: copies the position of another actor plus an offset row, then runs the route. */
MATCH void Actor_RunAttach(void* work_index) {
    Actor* work;
    Actor* tail;
    s32    delta[3];
    u8     index;

    index = Script_FindSlot(FIELD(u8, g_Task, 0x18));
    work  = TASK(Actor);
    if (work->timer == 0) {
        work->active_flags |= 0x20;
        work              = TASK(Actor);
        work->pos.x.fixed = g_Actors[index].pos.x.fixed;
        work->pos.y.fixed = g_Actors[index].pos.y.fixed;
        work->pos.z.fixed = g_Actors[index].pos.z.fixed;
        if (work->unk_06 != 0xA) {
            work->angle_x = g_Actors[index].angle_x;
            work->angle_y = g_Actors[index].angle_y;
            work->angle_z = g_Actors[index].angle_z;
        }
        func_801AC1DC(delta, FIELD(u8, g_Task, 0x1Cu));
        work = TASK(Actor);
        work->pos.x.fixed += delta[0];
        work->pos.y.fixed += delta[1];
        COORD_INT(work->pos.z) += delta[2];
    }
    Actor_RunRoute(work_index);
    tail = TASK(Actor);
    tail->direction &= 7;
}
