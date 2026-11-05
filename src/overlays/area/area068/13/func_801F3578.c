#include "area068_13.h"

MATCH void func_801F3578(void) {
    u8* counter;

    if (--D_801F4E00 == 0) {
        g_SpadWork->unk_01 = 0x14;
    } else if (g_InputPressed == 0x40) {
        D_801F4E0C = 0;
        D_801F4E04 += 1;
        g_SpadWork->unk_01 = 0x11;
        counter            = &D_80146865;
        *counter += 1;
    } else if (++D_801F4E0C >= 0x1C) {
        g_SpadWork->unk_01 = 0x16;
    } else {
        g_SpadWork->unk_01 = 0x10;
    }
}
