#include "area103_13.h"

MATCH void func_801F3C14(void) {
    Actor* work = g_Task;

    work->unk_09         = 0;
    work->x.fixed        = 0x570000;
    work->y.fixed        = 0x140000;
    work->z.part.integer = -0x100;
    work->unk_32         = 0;
    g_Task->unk_0B       = 0;
    g_Task->step++;
}
