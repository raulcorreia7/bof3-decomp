#include "area048_13.h"

MATCH void func_801F2CA4(void) {
    s32 temp_v0;

    ((Actor*)g_SpadWork)->unk_06  = 1;
    ((Actor*)g_SpadWork)->unk_0C  = 0x608000;
    ((Actor*)g_SpadWork)->unk_18  = 0x6B8000;
    ((Actor*)g_SpadWork)->unk_1C  = 0x118000;
    ((Actor*)g_SpadWork)->unk_10  = 0x118000;
    temp_v0                       = (Area_SampleHeight(((Actor*)g_SpadWork)->unk_0C, 0x118000) << 0x10) + 0x01000000;
    ((Actor*)g_SpadWork)->gravity = temp_v0;
    ((Actor*)g_SpadWork)->vz      = temp_v0;
    func_801F302C(&((Actor*)g_SpadWork)->unk_0C, &((Actor*)g_SpadWork)->unk_18, ((Actor*)g_SpadWork));
    func_801F2EC0();
    if (SYS_TestFlag(g_SceneEventFlags, 0xD) == 0) {
        ((Actor*)g_SpadWork)->unk_01 = 2;
    }
}
