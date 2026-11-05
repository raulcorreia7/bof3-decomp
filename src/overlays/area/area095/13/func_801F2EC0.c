#include "area095_13.h"

MATCH void func_801F2EC0(void) {
    Actor* work;

    func_801F2F3C(g_SpadWork->z.fixed, g_SpadWork->unk_0B & 0xF8);
    work = g_SpadWork;
    work->unk_0B -= 2;
    work->z.fixed += 1;
    if (g_SpadWork->z.fixed >= -0xBF) {
        func_80196070(g_SpadWork);
    }
}
