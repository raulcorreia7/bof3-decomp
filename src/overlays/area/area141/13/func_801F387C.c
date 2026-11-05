#include "area141_13.h"

MATCH void func_801F387C(void) {
    Actor* work;

    g_Task->flags |= 0x20;
    g_Task->flags &= 0xBF;
    g_Task->tint.bytes.flags       = 1;
    work                           = g_Task;
    work->tint.signed_bytes.unk_5F = -0x80;
    work->tint.signed_bytes.unk_5E = -0x80;
    work->tint.signed_bytes.unk_5D = -0x80;
    func_801F390C();
    g_Task->unk_04 = 1;
}
