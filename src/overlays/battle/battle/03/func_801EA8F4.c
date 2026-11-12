#include "battle_03.h"

MATCH void func_801EA8F4(void) {
    s32 offset;
    u8  value;
    s8  next;

    func_801EAAB8();
    if (((D_801EB5B0[D_801EBF04 * 8] & 0x1) != 0) && (g_InputPressed != 0) && ((func_801EAB38() & BYTE_MASK) != 0)) {
        g_MenuCurrentPanel->state = 3;
    }
    offset = D_801EBF04 * 8;
    if ((D_801EB5B0[offset] & 0x2) != 0) {
        value = D_801EB5B1[offset];
        if ((value & BYTE_MASK) != GAME_NONE) {
            next               = value - 1;
            D_801EB5B1[offset] = next;
            if (((next & BYTE_MASK) == 0) && ((func_801EAB38() & BYTE_MASK) != 0)) {
                g_MenuCurrentPanel->state = 3;
            }
        }
    }
}
