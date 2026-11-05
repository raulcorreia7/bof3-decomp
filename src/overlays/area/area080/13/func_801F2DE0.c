#include "area080_13.h"

MATCH void func_801F2DE0(void) {
    u8 temp_v0;

    func_801F30B0(D_801F44A0);
    func_801F31A0(D_801F44A0);
    func_801F3870();
    func_801F395C();
    temp_v0                      = ((Actor*)g_SpadWork)->unk_09 - 1;
    ((Actor*)g_SpadWork)->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        ((Actor*)g_SpadWork)->unk_09 = 0x1E;
        ((Actor*)g_SpadWork)->unk_01 += 1;
    }
}
