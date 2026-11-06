#include "area095_13.h"

MATCH void func_801F2EC0(void) {
    Actor* work;

    func_801F2F3C(g_Task->z.fixed, g_Task->unk_0B & 0xF8);
    work = g_Task;
    work->unk_0B -= 2;
    work->z.fixed += 1;
    if (g_Task->z.fixed >= -0xBF) {
        Actor_Clear();
    }
}
