#include "area103_13.h"

MATCH void func_801F3F60(void) {
    if (COORD_INT(SELF(Actor)->pos.x) >= 79) {
        SELF(Actor)->pos.x.fixed -= 0x1000;
    } else if (((g_FrameCount / 5) & 0x3) == 3) {
        SELF(Actor)->header.step++;
    }
    Area_StepSceneFrame();
}
