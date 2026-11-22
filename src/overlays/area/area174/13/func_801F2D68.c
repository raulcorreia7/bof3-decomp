#include "area174_13.h"

MATCH void func_801F2D68(void) {
    s32 result;

    if (!(TASK(Actor)->timer & 0x7)) {
        result = func_801F2E88();
        if (result != 0) {
            func_801F3378(result);
        }
    }
    TASK(Actor)->timer += 1;
    if (TASK(Actor)->unk_06 != 0) {
        Area_UpdateShots();
    }
    if (D_80147A8C == TO_COORD(64) + COORD_HALF) {
        TASK(Actor)->header.mode += 1;
    }
}
