#include "game_00.h"

MATCH void func_8019CEDC(void) {
    Actor* work;
    s32    moved;

    g_Task->unk_09 = (g_Task->unk_09 - 1);
    work           = g_Task;
    work->x.fixed += work->vx;
    moved         = work->y.fixed + work->vy;
    work->y.fixed = moved;
    if (work->unk_09 == 0) {
        if (LOHU(g_GameAreaId) == 0x54) {
            if ((work->x.fixed == 0x118000) && (moved == 0x4A8000)) {
                SYS_SetFlag(g_SceneEventFlags, 0x36);
            } else {
                SYS_ClearFlag(g_SceneEventFlags, 0x36);
            }
        }
        func_8019D270();
        g_Task->unk_0B = 0;
        g_Task->mode   = 1;
    }
    func_8015A944();
}
