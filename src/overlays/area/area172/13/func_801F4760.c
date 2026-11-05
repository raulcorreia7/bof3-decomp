#include "area172_13.h"

MATCH void func_801F4760(void) {
    Actor* work;

    g_Task->flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    g_Task->flags &= ~ACTOR_FLAG_HIDDEN;
    g_Task->tint.signed_bytes.flags = 1;
    work                            = g_Task;
    work->tint.signed_bytes.unk_5F  = -0x80;
    work->tint.signed_bytes.unk_5E  = -0x80;
    work->tint.signed_bytes.unk_5D  = -0x80;
    func_801F47F0();
    g_Task->unk_04 = 1;
}
