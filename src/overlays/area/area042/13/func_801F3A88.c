#include "area042_13.h"

MATCH void func_801F3A88(void) {
    Area_SetPosX(D_801F534C[TASK(Actor)->timer >> 1]);
    TASK(Actor)->timer += 1;
    if (TASK(Actor)->timer >= 5U) {
        TASK(Actor)->timer = 0;
        TASK(Actor)->header.step += 1;
    }
}
