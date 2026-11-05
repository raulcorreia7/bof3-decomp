#include "game_00.h"

MATCH void func_801A3410(void* work_index) {
    Actor* work;
    Actor* tail;
    s32    delta[3];
    u8     index;

    index = func_8015B4F4(FIELD(u8, g_Task, 0x18));
    work  = g_Task;
    if (work->unk_09 == 0) {
        work->active_flags |= 0x20;
        work          = g_Task;
        work->x.fixed = g_Actors[index].x.fixed;
        work->y.fixed = g_Actors[index].y.fixed;
        work->z.fixed = *(s32*)((u8*)&D_801468C4 + index * ACTOR_SIZE);
        if (work->unk_06 != 0xA) {
            work->unk_64 = g_Actors[index].unk_64;
            work->unk_68 = g_Actors[index].unk_68;
            work->unk_6C = g_Actors[index].unk_6C;
        }
        func_801AC1DC(delta, FIELD(u8, g_Task, 0x1Cu));
        work = g_Task;
        work->x.fixed += delta[0];
        work->y.fixed += delta[1];
        work->z.part.integer += delta[2];
    }
    func_801A1384(work_index);
    tail = g_Task;
    tail->direction_08 &= 7;
}
