#include "game_00.h"

MATCH void func_8019CEDC(void) {
    Actor* work;
    s32    moved;

    g_SpadWork->unk_09 = (u8)(g_SpadWork->unk_09 - 1);
    work               = g_SpadWork;
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
        g_SpadWork->unk_0B = 0;
        g_SpadWork->unk_01 = 1;
    }
    func_8015A944();
}
