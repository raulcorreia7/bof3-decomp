#include "area048_13.h"

MATCH void func_801F4B40(void) {
    u8* flags;
    u8  value;

    flags      = &g_ActorTurnRamps[1].flags;
    value      = *flags;
    D_8014686B = 0;
    *flags     = value | 0x1;
}
