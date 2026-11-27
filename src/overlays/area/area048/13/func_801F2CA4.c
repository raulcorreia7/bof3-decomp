#include "area048_13.h"

MATCH void func_801F2CA4(void) {
    s32 value;

    SELF(Actor)->unk_06  = 1;
    SELF(Actor)->vx      = 6324224;
    SELF(Actor)->unk_18  = 0x6B8000;
    SELF(Actor)->unk_1C  = 0x118000;
    SELF(Actor)->vy      = 1146880;
    value                = (Area_HeightSample(SELF(Actor)->vx, 0x118000) << 0x10) + 0x01000000;
    SELF(Actor)->gravity = value;
    SELF(Actor)->vz      = value;
    func_801F302C(&SELF(Actor)->vx, &SELF(Actor)->unk_18, SELF(Actor));
    func_801F2EC0();
    if (SYS_TestFlag(g_SceneEventFlags, 13) == 0) {
        SELF(Actor)->header.mode = 2;
    }
}
