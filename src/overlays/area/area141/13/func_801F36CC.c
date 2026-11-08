#include "area141_13.h"

MATCH void func_801F36CC(void) {
    Actor* task;
    s8     one;

    task = g_Task;
    task->header.flags |= 0x20;
    task                           = g_Task;
    task->tint.signed_bytes.unk_5F = -0x3C;
    task->tint.signed_bytes.unk_5E = -0x3C;
    task->tint.signed_bytes.unk_5D = -0x3C;
    one                            = 1;
    g_Task->tint.bytes.flags       = one;
    func_801F3740();
    g_Task->unk_04 = one;
}
