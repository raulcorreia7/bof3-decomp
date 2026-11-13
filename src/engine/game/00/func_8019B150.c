#include "game_00.h"

MATCH void func_8019B150(void) {
    Actor* work;
    s32    flag;

    flag = 1;
    Area_SelectSceneRecord(g_Task->unk_2C);

    g_Task->unk_48 = flag;

    g_Task->active_flags = 0;

    work         = g_Task;
    work->unk_2A = (work->unk_06 >> 7);

    Actor_SelectScript((g_Task->unk_06 & 0x7F));
    g_Task->header.mode = flag;
}
