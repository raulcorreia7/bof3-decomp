#include "area042_13.h"

MATCH void func_801F3720(void) {
    Actor* work;

    func_801F37A8(g_Task->z.fixed, (g_Task->unk_0B & 0xF8) << 0x10);
    work = g_Task;
    work->unk_0B -= 4;
    work->z.fixed += 4;
    if (g_Task->z.fixed >= -0x7F) {
        D_801448EC = 4;
        Actor_Clear();
    }
}
