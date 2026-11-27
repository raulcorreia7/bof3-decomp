#include "area042_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2C84(void) {
    s16 height;
    s32 value;
    FAKE_STACK_PADS(u8, 16); /* FAKE: retail's frame is 0x28, the body's locals take 0x18. */

    height                        = Area_HeightSample(SELF(Actor)->vx, SELF(Actor)->vy);
    value                         = (height << 0x10) + TO_COORD(0x100);
    SELF(Actor)->vz               = value;
    SELF(Actor)->gravity          = value;
    COORD_INT(SELF(Actor)->pos.z) = height;
    SELF(Actor)->voice_flags.raw  = 0;
    if (SYS_TestFlag(g_SceneEventFlags, 0xB) == 0) {
        SELF(Actor)->header.mode = 1;
    } else {
        SELF(Actor)->header.mode = 2;
    }
}
#else
INCLUDE_ASM(func_801F2C84);
#endif
