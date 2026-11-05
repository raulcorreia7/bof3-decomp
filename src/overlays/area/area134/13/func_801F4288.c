#include "area134_13.h"

MATCH void func_801F4288(void) {
    u8 temp_v0;

    if (!(g_SpadWork->unk_09 & 3)) {
        func_801F48B0();
    }
    temp_v0            = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_SpadWork->unk_01 += 1;
    }
    func_801F49A0();
}
