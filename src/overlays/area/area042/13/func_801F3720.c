#include "area042_13.h"

MATCH void func_801F3720(void) {
    Actor* work;

    func_801F37A8(g_SpadWork->z.fixed, (g_SpadWork->unk_0B & 0xF8) << 0x10);
    work = g_SpadWork;
    work->unk_0B -= 4;
    work->z.fixed += 4;
    if (g_SpadWork->z.fixed >= -0x7F) {
        D_801448EC = 4;
        func_80196070(g_SpadWork);
    }
}
