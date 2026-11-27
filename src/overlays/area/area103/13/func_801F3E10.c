#include "area103_13.h"

MATCH void func_801F3E10(void) {
    if (COORD_INT(SELF(Actor)->pos.y) < 25) {
        SELF(Actor)->pos.y.fixed += 0x1000;
    } else {
        SELF(Actor)->header.step++;
    }
    Area_StepSceneFrame();
}
