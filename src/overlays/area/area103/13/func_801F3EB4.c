#include "area103_13.h"

MATCH void func_801F3EB4(void) {
    if (COORD_INT(TASK(Actor)->pos.y) < 28) {
        TASK(Actor)->pos.x.fixed -= 0x800;
        TASK(Actor)->pos.y.fixed += 0x800;
    } else {
        TASK(Actor)->header.step++;
    }
    Area_StepSceneFrame();
}
