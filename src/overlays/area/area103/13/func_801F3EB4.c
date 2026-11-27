#include "area103_13.h"

MATCH void func_801F3EB4(void) {
    if (COORD_INT(SELF(Actor)->pos.y) < 28) {
        SELF(Actor)->pos.x.fixed -= 0x800;
        SELF(Actor)->pos.y.fixed += 0x800;
    } else {
        SELF(Actor)->header.step++;
    }
    Area_StepSceneFrame();
}
