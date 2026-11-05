#include "area172_13.h"

MATCH void func_801F4760(void) {
    Actor* work;

    g_SpadWork->flags_00 |= ACTOR_FLAG_SEMI_TRANSPARENT;
    g_SpadWork->flags_00 &= ~ACTOR_FLAG_HIDDEN;
    g_SpadWork->tint.signed_bytes.flags = 1;
    work = g_SpadWork;
    work->tint.signed_bytes.unk_5F = -0x80;
    work->tint.signed_bytes.unk_5E = -0x80;
    work->tint.signed_bytes.unk_5D = -0x80;
    func_801F47F0();
    g_SpadWork->unk_04 = 1;
}
