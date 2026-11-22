#include "area048_13.h"

MATCH void func_801F2CA4(void) {
    s32 value;

    TASK(Actor)->unk_06  = 1;
    TASK(Actor)->vx      = 6324224;
    TASK(Actor)->unk_18  = 0x6B8000;
    TASK(Actor)->unk_1C  = 0x118000;
    TASK(Actor)->vy      = 1146880;
    value                = (Area_HeightSample(TASK(Actor)->vx, 0x118000) << 0x10) + 0x01000000;
    TASK(Actor)->gravity = value;
    TASK(Actor)->vz      = value;
    func_801F302C(&TASK(Actor)->vx, &TASK(Actor)->unk_18, TASK(Actor));
    func_801F2EC0();
    if (SYS_TestFlag(g_SceneEventFlags, 13) == 0) {
        TASK(Actor)->header.mode = 2;
    }
}
