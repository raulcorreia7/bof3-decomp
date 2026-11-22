#include "battle_03.h"

MATCH void func_801DD800(void) {
    u8* ptr;

    u8 value;
    /* FAKE: the -2 operand is a live copy in a1 in the retail tail. */
    FAKE_REG(u8, keep, "a1");
    /* FAKE: v0 holds the step result so a0/a1 stay live at the latch compare. */
    FAKE_REG(u8, next, "v0");

    ptr   = &g_Battle.unk_24[4];
    value = *ptr;
    if (value > 0x1Eu) {
        g_Battle.unk_24[0] = 1;
    }
    keep = value;
    if (value == 0) {
        g_Battle.unk_24[0] = 0;
    }
    if (g_Battle.unk_24[0] == 1) {
        next = keep - 2;
    } else {
        next = value + 2;
    }
    *ptr = next;
}
