#include "area052_13.h"

MATCH void func_801F2DCC(void) {
    if (TASK(Actor)->timer == 0) {
        func_801F3084();
    }
    TASK(Actor)->timer += 1;
    if (TASK(Actor)->timer == 4) {
        TASK(Actor)->timer = 0;
        TASK(Actor)->unk_06 += 1;
    }
    Area_UpdateEffectRows();
    if (TASK(Actor)->unk_06 == TASK(Actor)->param.unk_0B) {
        TASK(Actor)->header.mode += 1;
    }
}
