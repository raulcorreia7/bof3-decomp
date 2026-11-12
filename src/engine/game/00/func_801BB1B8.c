#include "game_00.h"

/* The retail code never reads $a0; the caller's argument is a leftover register value kept in the prototype. */
MATCH bool func_801BB1B8(void) {
    u8 mode;

    mode = SP_REF(u8, 0x8);
    if (mode == 0x10 || mode == 0x20) {
        if ((SP_REF(u8, 0x9) == 0x10 || SP_REF(u8, 0x9) == 0x20) && (SP_REF(u8, 0xA) == 0x10 || SP_REF(u8, 0xA) == 0x20)) {
            return 1;
        }
        if (SP_REF(u8, 0x9) == 0x10 || SP_REF(u8, 0x9) == 0x20) {
            func_801BB8E8(2, 4, 3);
            return 0;
        }
        if (SP_REF(u8, 0xA) == 0x10 || SP_REF(u8, 0xA) == 0x20) {
            func_801BB8E8(4, 6, 5);
            return 0;
        }
        g_Task->direction_08 = (g_Task->direction_08 + 1) & 0x7;
    }
    return 0;
}
