#include "area172_13.h"

MATCH void func_801F4AF4(void) {
    Actor* work;
    SELF(Actor)->header.flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
    SELF(Actor)->tint.bytes.flags = 0;
    work                          = SELF(Actor);
    work->tint.bytes.rgb.b        = 0;
    work->tint.bytes.rgb.g        = 0;
    work->tint.bytes.rgb.r        = 0;
}
