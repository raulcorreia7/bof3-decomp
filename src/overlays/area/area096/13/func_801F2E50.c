#include "area096_13.h"
#include "work/area_spad.h"

MATCH void func_801F2E50(void) {
    Actor* work;

    func_801F2ECC(g_SpadWork->z.fixed, g_SpadWork->unk_0B & 0xF8);
    work = g_SpadWork;
    work->unk_0B -= 2;
    work->z.fixed += 1;
    if (g_SpadWork->z.fixed >= -0xBF) {
        func_80196070(g_SpadWork);
    }
}
