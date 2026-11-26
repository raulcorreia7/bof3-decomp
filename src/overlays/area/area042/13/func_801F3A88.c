#include "area042_13.h"

MATCH void func_801F3A88(void) {
    Area_SetPosX(D_801F534C[SELF(Actor)->timer >> 1]);
    SELF(Actor)->timer += 1;
    if (SELF(Actor)->timer >= 5U) {
        SELF(Actor)->timer = 0;
        SELF(Actor)->header.step += 1;
    }
}
