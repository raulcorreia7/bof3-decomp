#include "area042_13.h"

MATCH void func_801F3C88(void) {
    Area_SetPosX(D_801F5354[TASK(Actor)->timer >> 1]);
    TASK(Actor)->timer++;
    if (TASK(Actor)->timer >= 7) {
        TASK(Actor)->timer       = 0;
        TASK(Actor)->header.step = 3;
    }
}
