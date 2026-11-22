#include "area048_13.h"

MATCH void func_801F2D64(void) {
    s32 top;

    g_Task->unk_06  = 0;
    g_Task->vx      = TO_COORD_HALF(96);
    g_Task->unk_18  = TO_COORD_HALF(107);
    g_Task->unk_1C  = TO_COORD_HALF(13);
    g_Task->vy      = TO_COORD_HALF(13);
    top             = TO_COORD(Area_HeightSample(g_Task->vx, TO_COORD_HALF(13)) + 0x100);
    g_Task->gravity = top;
    g_Task->vz      = top;
    func_801F302C(&g_Task->vx, &g_Task->unk_18, g_Task);
    func_801F2EC0();

    g_Task->unk_06  = 2;
    g_Task->vx      = TO_COORD_HALF(96);
    g_Task->unk_18  = TO_COORD_HALF(107);
    g_Task->unk_1C  = TO_COORD_HALF(21);
    g_Task->vy      = TO_COORD_HALF(21);
    top             = TO_COORD(Area_HeightSample(g_Task->vx, TO_COORD_HALF(21)) + 0x100);
    g_Task->gravity = top;
    g_Task->vz      = top;
    func_801F302C(&g_Task->vx, &g_Task->unk_18, g_Task);
    func_801F2EC0();

    if (SYS_TestFlag(g_SceneEventFlags, 13) != 0) {
        g_Task->header.mode = 1;
    }
}
