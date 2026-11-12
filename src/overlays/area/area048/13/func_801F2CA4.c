#include "area048_13.h"

MATCH void func_801F2CA4(void) {
    s32 value;

    g_Task->unk_06  = 1;
    g_Task->vx      = 6324224;
    g_Task->unk_18  = 0x6B8000;
    g_Task->unk_1C  = 0x118000;
    g_Task->vy      = 1146880;
    value           = (Area_SampleHeight(g_Task->vx, 0x118000) << 0x10) + 0x01000000;
    g_Task->gravity = value;
    g_Task->vz      = value;
    func_801F302C(&g_Task->vx, &g_Task->unk_18, g_Task);
    func_801F2EC0();
    if (SYS_TestFlag(g_SceneEventFlags, 13) == 0) {
        g_Task->header.mode = 2;
    }
}
