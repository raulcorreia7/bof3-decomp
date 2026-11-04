#include "area042_13.h"

MATCH void func_801F36BC(void) {
    Actor* work;

    func_801F37A8(g_SpadWork->z.fixed, 0x800000);
    work = g_SpadWork;
    work->z.fixed += 4;
    if (work->z.fixed >= -0xFF) {
        work->state_02++;
    }
}
