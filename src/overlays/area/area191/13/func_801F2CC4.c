#include "area191_13.h"

MATCH void func_801F2CC4(void) {
    Actor* work;

    work                    = g_Task;
    work->tint.bytes.unk_5F = 0;
    work->tint.bytes.unk_5E = 0;
    work->tint.bytes.unk_5D = 0;
    g_Task->timer           = 0x3C;
    g_Task->header.mode     = 1;
}
