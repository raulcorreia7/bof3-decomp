#include "area175_13.h"

MATCH void func_801F3228(void) {
    Actor* work;

    g_Task->timer           = 0x10;
    g_Task->header.mode     = 1;
    work                    = g_Task;
    work->tint.bytes.unk_5F = 0;
    work->tint.bytes.unk_5E = 0;
    work->tint.bytes.unk_5D = 0;
}
