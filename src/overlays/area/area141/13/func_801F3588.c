#include "area141_13.h"

MATCH void func_801F3588(void) {
    Actor* actor;

    g_SpadWork->flags_00 &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
    actor                    = g_SpadWork;
    actor->tint.bytes.unk_5F = 0;
    actor->tint.bytes.unk_5E = 0;
    actor->tint.bytes.unk_5D = 0;
    actor->tint.bytes.flags  = 0;
    GFX_FreePaletteFadeTarget(g_SpadWork);
}
