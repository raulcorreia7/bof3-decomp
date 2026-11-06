#include "area107_13.h"
#include "work/area_spad.h"

MATCH void func_801F2D4C(void) {
    Actor* work;
    s32    timer;
    s8     step;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & 0xFF)) {
        Message_StartAreaMessage(1);
        work              = g_Task;
        g_GameStateIndex  = GAME_REQUEST_MESSAGE;
        work->header.mode = 4;
    } else {
        step                     = D_801F2E58[g_Task->unk_09 & 3];
        g_AreaCameraRefreshCount = 2;
        g_AreaCameraOffsetY += step * 4;
    }
}
