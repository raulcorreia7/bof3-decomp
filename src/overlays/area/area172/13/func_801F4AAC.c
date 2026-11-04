#include "area172_13.h"

MATCH void func_801F4AAC(void) {
    Actor* work;
    g_SpadWork->flags_00 |= ACTOR_FLAG_SEMI_TRANSPARENT;
    g_SpadWork->tint.bytes.flags   = 1;
    work                           = g_SpadWork;
    work->tint.signed_bytes.unk_5F = -0x40;
    work->tint.signed_bytes.unk_5E = -0x40;
    work->tint.signed_bytes.unk_5D = -0x40;
}
