#include "area052_13.h"

MATCH void func_801F2DCC(void) {
    if (SELF(Actor)->timer == 0) {
        func_801F3084();
    }
    SELF(Actor)->timer += 1;
    if (SELF(Actor)->timer == 4) {
        SELF(Actor)->timer = 0;
        SELF(Actor)->unk_06 += 1;
    }
    Area_UpdateEffectRows();
    if (SELF(Actor)->unk_06 == SELF(Actor)->param.unk_0B) {
        SELF(Actor)->header.mode += 1;
    }
}
