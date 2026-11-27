#include "area141_13.h"

MATCH void func_801F3588(void) {
    Actor* actor;

    SELF(Actor)->header.flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
    actor                   = SELF(Actor);
    actor->tint.bytes.rgb.b = 0;
    actor->tint.bytes.rgb.g = 0;
    actor->tint.bytes.rgb.r = 0;
    actor->tint.bytes.flags = 0;
    GFX_PaletteFreeFadeTarget(g_Self);
}
