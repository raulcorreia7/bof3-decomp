#include "area042_13.h"

MATCH void func_801F3C88(void) {
    Area_SetPosX(D_801F5354[SELF(Actor)->timer >> 1]);
    SELF(Actor)->timer++;
    if (SELF(Actor)->timer >= 7) {
        SELF(Actor)->timer       = 0;
        SELF(Actor)->header.step = 3;
    }
}
