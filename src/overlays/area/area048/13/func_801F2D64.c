#include "area048_13.h"

MATCH void func_801F2D64(void) {
    s32 top;

    SELF(Actor)->unk_06  = 0;
    SELF(Actor)->vx      = TO_COORD_HALF(96);
    SELF(Actor)->unk_18  = TO_COORD_HALF(107);
    SELF(Actor)->unk_1C  = TO_COORD_HALF(13);
    SELF(Actor)->vy      = TO_COORD_HALF(13);
    top                  = TO_COORD(Area_HeightSample(SELF(Actor)->vx, TO_COORD_HALF(13)) + 0x100);
    SELF(Actor)->gravity = top;
    SELF(Actor)->vz      = top;
    func_801F302C(&SELF(Actor)->vx, &SELF(Actor)->unk_18, SELF(Actor));
    func_801F2EC0();

    SELF(Actor)->unk_06  = 2;
    SELF(Actor)->vx      = TO_COORD_HALF(96);
    SELF(Actor)->unk_18  = TO_COORD_HALF(107);
    SELF(Actor)->unk_1C  = TO_COORD_HALF(21);
    SELF(Actor)->vy      = TO_COORD_HALF(21);
    top                  = TO_COORD(Area_HeightSample(SELF(Actor)->vx, TO_COORD_HALF(21)) + 0x100);
    SELF(Actor)->gravity = top;
    SELF(Actor)->vz      = top;
    func_801F302C(&SELF(Actor)->vx, &SELF(Actor)->unk_18, SELF(Actor));
    func_801F2EC0();

    if (SYS_TestFlag(g_SceneEventFlags, 13) != 0) {
        SELF(Actor)->header.mode = 1;
    }
}
