#include "area103_13.h"

MATCH void func_801F41EC(void) {
    s16 remaining;

    if (SELF(Actor)->timer == 15) {
        SELF(Actor)->timer = 0;
    }
    remaining = SELF(Actor)->unk_32;
    if (remaining > 0) {
        SELF(Actor)->unk_32 = remaining - 1;
    } else if (!((SELF(Actor)->timer / 5) & BYTE_MASK)) {
        SELF(Actor)->header.step += 1;
    }
    if (!((SELF(Actor)->timer % 5) & BYTE_MASK)) {
        func_801F4E70(((SELF(Actor)->timer / 5) & BYTE_MASK) + 7);
    }
    SELF(Actor)->timer += 1;
    func_801F49A0(1);
}
