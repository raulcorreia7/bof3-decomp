#include "area103_13.h"

MATCH void func_801F4FD4(void) {
    u8 temp_a0;

    func_801F5174(7, 0x80);
    temp_a0 = g_SpadWork->unk_09;
    if (temp_a0 < 0x10U) {
        func_801F53F0(temp_a0);
    }
    g_SpadWork->unk_09 += 1;
    if ((u8)g_SpadWork->unk_09 >= 0x20U) {
        g_SpadWork->unk_09 = 0;
        g_SpadWork->state_02 += 1;
    }
}
