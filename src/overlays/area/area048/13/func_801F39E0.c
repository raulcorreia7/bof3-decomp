#include "area048_13.h"

MATCH void func_801F39E0(void) {
    func_801F3AE4(0x400, 0x858000 - (g_SpadWork->unk_09 << 0xC), 0x10);
    func_801F3AE4(0xC00, (g_SpadWork->unk_09 << 0xC) + 0x878000, 0x11);
    g_SpadWork->unk_09 += 1;
    if ((u8)g_SpadWork->unk_09 >= 0x11U) {
        g_SpadWork->state_02 += 1;
        g_SpadWork->unk_09 = 0;
    }
}
