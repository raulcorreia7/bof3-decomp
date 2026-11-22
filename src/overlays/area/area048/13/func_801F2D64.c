#include "area048_13.h"

MATCH void func_801F2D64(void) {
    s32 top;

    TASK(Actor)->unk_06  = 0;
    TASK(Actor)->vx      = TO_COORD_HALF(96);
    TASK(Actor)->unk_18  = TO_COORD_HALF(107);
    TASK(Actor)->unk_1C  = TO_COORD_HALF(13);
    TASK(Actor)->vy      = TO_COORD_HALF(13);
    top                  = TO_COORD(Area_HeightSample(TASK(Actor)->vx, TO_COORD_HALF(13)) + 0x100);
    TASK(Actor)->gravity = top;
    TASK(Actor)->vz      = top;
    func_801F302C(&TASK(Actor)->vx, &TASK(Actor)->unk_18, TASK(Actor));
    func_801F2EC0();

    TASK(Actor)->unk_06  = 2;
    TASK(Actor)->vx      = TO_COORD_HALF(96);
    TASK(Actor)->unk_18  = TO_COORD_HALF(107);
    TASK(Actor)->unk_1C  = TO_COORD_HALF(21);
    TASK(Actor)->vy      = TO_COORD_HALF(21);
    top                  = TO_COORD(Area_HeightSample(TASK(Actor)->vx, TO_COORD_HALF(21)) + 0x100);
    TASK(Actor)->gravity = top;
    TASK(Actor)->vz      = top;
    func_801F302C(&TASK(Actor)->vx, &TASK(Actor)->unk_18, TASK(Actor));
    func_801F2EC0();

    if (SYS_TestFlag(g_SceneEventFlags, 13) != 0) {
        TASK(Actor)->header.mode = 1;
    }
}
