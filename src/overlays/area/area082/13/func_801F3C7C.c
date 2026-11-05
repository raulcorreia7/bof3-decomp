#include "area082_13.h"

MATCH void func_801F3C7C(void) {
    g_SpadWork->unk_09 += 1;
    if ((u8)g_SpadWork->unk_09 >= 0x11U) {
        g_SpadWork->unk_09 = 0;
        g_SpadWork->unk_0B = 1;
        g_SpadWork->state_02 += 1;
    }
    func_801F4430();
}
