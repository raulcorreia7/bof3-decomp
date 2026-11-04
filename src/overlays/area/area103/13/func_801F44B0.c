#include "area103_13.h"

MATCH void func_801F44B0(void) {
    if (g_SpadWork->unk_09 % 5 == 0) {
        func_801F4E70(g_SpadWork->unk_09 / 5 + 4);
    }
    g_SpadWork->unk_09++;
    if (g_SpadWork->unk_09 / 5 == 3) {
        g_SpadWork->state_02++;
        g_SpadWork->unk_09 = 1;
    }
}
