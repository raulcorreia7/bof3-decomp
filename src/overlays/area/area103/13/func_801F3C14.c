#include "area103_13.h"

MATCH void func_801F3C14(void) {
    Actor* work = g_Task;

    work->unk_09           = 0;
    work->pos.x.fixed      = 0x570000;
    work->pos.y.fixed      = 0x140000;
    COORD_INT(work->pos.z) = -0x100;
    work->unk_32           = 0;
    g_Task->unk_0B         = 0;
    g_Task->header.step++;
}
