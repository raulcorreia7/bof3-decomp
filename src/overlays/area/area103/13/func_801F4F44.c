#include "area103_13.h"

MATCH void func_801F4F44(void) {
    func_801F5174(g_SpadWork->unk_09, 0x80);
    func_801F53F0(g_SpadWork->unk_09);
    g_SpadWork->unk_09 += 1;
    if ((u8)g_SpadWork->unk_09 >= 8U) {
        g_SpadWork->state_02 += 1;
    }
}
