#include "area080_13.h"

MATCH void func_801F3018(void) {
    u8 remaining;

    D_801F44A0->unk_23 -= 3;
    Area_ProjectRing(D_801F44A0);
    func_801F31A0(D_801F44A0);
    func_801F33DC(D_801F44A0);
    func_801F3870();
    remaining     = g_Task->timer - 1;
    g_Task->timer = remaining;
    if (!(remaining & BYTE_MASK)) {
        func_80196070();
    }
}
