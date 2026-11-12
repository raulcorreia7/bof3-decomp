#include "area174_13.h"

MATCH void func_801F3FFC(void) {
    s8     tint_a;
    s8     tint_b;
    s8     tint_c;
    Actor* work;
    Actor* scratch;

    work = g_Task;
    COORD_INT(work->pos.z) -= 0x14;
    tint_a = work->tint.signed_bytes.unk_5D;
    if (tint_a < -0x40) {
        work->tint.signed_bytes.unk_5D = tint_a + 2;
    }
    scratch = g_Task;
    tint_b  = scratch->tint.signed_bytes.unk_5E;
    if (tint_b < -0x40) {
        scratch->tint.signed_bytes.unk_5E = tint_b + 2;
        scratch                           = g_Task;
    }
    tint_c = scratch->tint.signed_bytes.unk_5F;
    if (tint_c < -0x40) {
        scratch->tint.signed_bytes.unk_5F = tint_c + 2;
    }
    if (COORD_INT(g_Task->pos.z) == 0xA00) {
        g_Task->header.flags &= ~0x20;
        g_Task->tint.bytes.flags = 0;
        {
            Actor* task             = g_Task;
            task->tint.bytes.unk_5F = 0;
            task->tint.bytes.unk_5E = 0;
            task->tint.bytes.unk_5D = 0;
        }
    } else {
        g_CurrentActor->unk_7E -= 2;
    }
}
