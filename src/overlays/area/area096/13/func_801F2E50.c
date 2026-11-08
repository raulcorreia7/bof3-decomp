#include "area096_13.h"
#include "area/spad.h"

MATCH void func_801F2E50(void) {
    Actor* work;

    func_801F2ECC(g_Task->pos.z.fixed, g_Task->param.unk_0B & 0xF8);
    work = g_Task;
    work->param.unk_0B -= 2;
    work->pos.z.fixed += 1;
    if (g_Task->pos.z.fixed >= -0xBF) {
        Actor_Clear();
    }
}
