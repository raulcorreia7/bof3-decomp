#include "game_00.h"

MATCH void func_801A3410(void* work_index) {
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
            work->unk_64 = g_Actors[index].unk_64;
            work->unk_68 = g_Actors[index].unk_68;
            work->unk_6C = g_Actors[index].unk_6C;
        }
        func_801AC1DC(delta, FIELD(u8, g_Task, 0x1Cu));
        work = TASK(Actor);
        work->pos.x.fixed += delta[0];
        work->pos.y.fixed += delta[1];
        COORD_INT(work->pos.z) += delta[2];
    }
    func_801A1384(work_index);
    tail = TASK(Actor);
    tail->direction &= 7;
}
