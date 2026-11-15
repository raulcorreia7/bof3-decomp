#include "area048_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2D64(void) {
    s32 value;

    g_Task->unk_06  = 0;
    g_Task->vx      = 0x608000;
    g_Task->unk_18  = 0x6B8000;
    g_Task->unk_1C  = 0xD8000;
    g_Task->vy      = 0xD8000;
    value           = (Area_SampleHeight(g_Task->vx, 0xD8000) << 0x10) + TO_COORD(0x100);
    g_Task->gravity = value;
    g_Task->vz      = value;
    func_801F302C(&g_Task->vx, &g_Task->unk_18, g_Task);
    func_801F2EC0();

    g_Task->unk_06  = 2;
    g_Task->vx      = 0x608000;
    g_Task->unk_18  = 0x6B8000;
    g_Task->unk_1C  = 0x158000;
    g_Task->vy      = 0x158000;
    value           = (Area_SampleHeight(g_Task->vx, 0x158000) << 0x10) + TO_COORD(0x100);
    g_Task->gravity = value;
    g_Task->vz      = value;
    func_801F302C(&g_Task->vx, &g_Task->unk_18, g_Task);
    func_801F2EC0();

    if (SYS_TestFlag(g_SceneEventFlags, 13) != 0) {
        g_Task->header.mode = 1;
    }
}
#else
INCLUDE_ASM(func_801F2D64);
#endif
