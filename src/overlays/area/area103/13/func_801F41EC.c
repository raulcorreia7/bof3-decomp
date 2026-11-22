#include "area103_13.h"

MATCH void func_801F41EC(void) {
    s16 remaining;

    if (TASK(Actor)->timer == 15) {
        TASK(Actor)->timer = 0;
    }
    remaining = TASK(Actor)->unk_32;
    if (remaining > 0) {
        TASK(Actor)->unk_32 = remaining - 1;
    } else if (!((TASK(Actor)->timer / 5) & BYTE_MASK)) {
        TASK(Actor)->header.step += 1;
    }
    if (!((TASK(Actor)->timer % 5) & BYTE_MASK)) {
        func_801F4E70(((TASK(Actor)->timer / 5) & BYTE_MASK) + 7);
    }
    TASK(Actor)->timer += 1;
    func_801F49A0(1);
}
