#include "area172_13.h"

MATCH void func_801F4AF4(void) {
    Actor* work;
    g_SpadWork->flags_00 &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
    g_SpadWork->tint.bytes.flags = 0;
    work                         = g_SpadWork;
    work->tint.bytes.unk_5F      = 0;
    work->tint.bytes.unk_5E      = 0;
    work->tint.bytes.unk_5D      = 0;
}
