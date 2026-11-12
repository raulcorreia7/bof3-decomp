#include "game_00.h"

MATCH void func_8019BE28(void) {
    Actor* work;

    g_Task->unk_48 = 2;
    work           = g_Task;
    work->scale.x += 0x4000;
    work->scale.y += 0x4000;
    if (work->timer != 0) {
        if (g_AreaCameraMoving == 0) {
            work->timer = (work->timer - 1);
        }
    }
    if (g_Task->scale.x > 131071) {
        if ((g_AreaCameraMoving == 0) && (g_Task->timer == 0)) {
            func_8019BFD4();
            Actor_Clear();
        }
    } else {
        Area_SetDrawMode();
    }
}
