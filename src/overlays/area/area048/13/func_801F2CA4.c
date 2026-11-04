#include "area048_13.h"

MATCH void func_801F2CA4(void) {
    s32 value;

    g_SpadWork->unk_06  = 1;
    g_SpadWork->unk_0C  = 0x608000;
    g_SpadWork->unk_18  = 0x6B8000;
    g_SpadWork->unk_1C  = 0x118000;
    g_SpadWork->unk_10  = 0x118000;
    value               = (Area_SampleHeight(g_SpadWork->unk_0C, 0x118000) << 0x10) + 0x01000000;
    g_SpadWork->gravity = value;
    g_SpadWork->vz      = value;
    func_801F302C(&g_SpadWork->unk_0C, &g_SpadWork->unk_18, g_SpadWork);
    func_801F2EC0();
    if (SYS_TestFlag(g_SceneEventFlags, 0xD) == 0) {
        g_SpadWork->unk_01 = 2;
    }
}
