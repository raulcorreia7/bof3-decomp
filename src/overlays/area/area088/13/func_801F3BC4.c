#include "area088_13.h"

MATCH void func_801F3BC4(void) {
    SELF(Actor)->active_flags = 0x80;
    Area_SceneSelectRecord(0x157);
    SELF(Actor)->draw_layer = 5;
    SELF(Actor)->mirror     = 0;
    ACTOR_CLEAR_TINT();
    SELF(Actor)->header.mode = 1;
}
