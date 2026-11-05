#include "area141_13.h"

MATCH void func_801F387C(void) {
    Actor* work;

    g_SpadWork->flags_00 |= 0x20;
    g_SpadWork->flags_00 &= 0xBF;
    g_SpadWork->tint.bytes.flags   = 1;
    work                           = g_SpadWork;
    work->tint.signed_bytes.unk_5F = -0x80;
    work->tint.signed_bytes.unk_5E = -0x80;
    work->tint.signed_bytes.unk_5D = -0x80;
    func_801F390C();
    g_SpadWork->unk_04 = 1;
}
