#include "area103_13.h"

MATCH void func_801F3E10(void) {
    if (COORD_INT(TASK(Actor)->pos.y) < 25) {
        TASK(Actor)->pos.y.fixed += 0x1000;
    } else {
        TASK(Actor)->header.step++;
    }
    Area_StepSceneFrame();
}
