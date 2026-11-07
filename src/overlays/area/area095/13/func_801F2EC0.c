#include "area095_13.h"

MATCH void func_801F2EC0(void) {
    Actor* work;

    func_801F2F3C(g_Task->pos.z.fixed, g_Task->param.unk_0B & 0xF8);
    work = g_Task;
    work->param.unk_0B -= 2;
    work->pos.z.fixed += 1;
    if (g_Task->pos.z.fixed >= -0xBF) {
        Actor_Clear();
    }
}
