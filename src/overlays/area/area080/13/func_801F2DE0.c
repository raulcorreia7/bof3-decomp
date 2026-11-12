#include "area080_13.h"

MATCH void func_801F2DE0(void) {
    u8 remaining;

    Area_ProjectRing(D_801F44A0);
    func_801F31A0(D_801F44A0);
    func_801F3870();
    func_801F395C();
    remaining               = ((Actor*)g_Task)->timer - 1;
    ((Actor*)g_Task)->timer = remaining;
    if (!(remaining & BYTE_MASK)) {
        ((Actor*)g_Task)->timer = 30;
        ((Actor*)g_Task)->header.mode += 1;
    }
}
