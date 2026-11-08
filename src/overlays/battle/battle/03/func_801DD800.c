#include "battle_03.h"

MATCH void func_801DD800(void) {
    u8* ptr;

    u8 value;
    /* FAKE: the -2 operand is a live copy in a1 in the retail tail. */
    FAKE_REG(u8, keep, "a1");
    /* FAKE: v0 holds the step result so a0/a1 stay live at the latch compare. */
    FAKE_REG(u8, next, "v0");

    ptr   = &D_80146308;
    value = *ptr;
    if (value > 0x1Eu) {
        D_80146304 = 1;
    }
    keep = value;
    if (value == 0) {
        D_80146304 = 0;
    }
    if (D_80146304 == 1) {
        next = keep - 2;
    } else {
        next = value + 2;
    }
    *ptr = next;
}
