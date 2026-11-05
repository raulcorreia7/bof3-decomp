#include "area125_13.h"

MATCH void func_801F2D6C(void) {
    u8 count;

    if (g_SpadWork->unk_09 % 15 == 0) {
        func_801F3268(2);
    }
    func_801F33B0();
    count              = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = count;
    if (count == 0) {
        g_SpadWork->unk_01 += 1;
    }
}
