#include "area048_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2D64(void) {
    s32 value;

    TASK(Actor)->unk_06  = 0;
    TASK(Actor)->vx      = 0x608000;
    TASK(Actor)->unk_18  = 0x6B8000;
    TASK(Actor)->unk_1C  = 0xD8000;
    TASK(Actor)->vy      = 0xD8000;
    value                = (Area_HeightSample(TASK(Actor)->vx, 0xD8000) << 0x10) + TO_COORD(0x100);
    TASK(Actor)->gravity = value;
    TASK(Actor)->vz      = value;
    func_801F302C(&TASK(Actor)->vx, &TASK(Actor)->unk_18, g_Task);
    func_801F2EC0();

    TASK(Actor)->unk_06  = 2;
    TASK(Actor)->vx      = 0x608000;
    TASK(Actor)->unk_18  = 0x6B8000;
    TASK(Actor)->unk_1C  = 0x158000;
    TASK(Actor)->vy      = 0x158000;
    value                = (Area_HeightSample(TASK(Actor)->vx, 0x158000) << 0x10) + TO_COORD(0x100);
    TASK(Actor)->gravity = value;
    TASK(Actor)->vz      = value;
    func_801F302C(&TASK(Actor)->vx, &TASK(Actor)->unk_18, g_Task);
    func_801F2EC0();

    if (SYS_TestFlag(g_SceneEventFlags, 13) != 0) {
        TASK(Actor)->header.mode = 1;
    }
}
#else
INCLUDE_ASM(func_801F2D64);
#endif
