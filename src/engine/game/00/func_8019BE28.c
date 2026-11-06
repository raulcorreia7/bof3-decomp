#include "game_00.h"

MATCH void func_8019BE28(void) {
    Actor* work;

    g_Task->unk_48 = 2;
    work           = g_Task;
    work->scale_x  = work->scale_x + 0x4000;
    work->scale_y  = work->scale_y + 0x4000;
    if (work->unk_09 != 0) {
        if (g_AreaCameraMoving == 0) {
            work->unk_09 = (work->unk_09 - 1);
        }
    }
    if (g_Task->scale_x > 0x1FFFF) {
        if ((g_AreaCameraMoving == 0) && (g_Task->unk_09 == 0)) {
            func_8019BFD4();
            Actor_Clear();
        }
    } else {
        Area_SetDrawMode();
    }
}
