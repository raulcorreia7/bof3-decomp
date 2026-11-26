#include "area033_13.h"

/* Each access reloads the work cell through g_Self. */
MATCH void func_801F2F94(void) {
    SELF(Actor)->active_flags = 0x80;
    Area_SceneSelectRecord(0xF);
    SELF(Actor)->draw_layer = 5;
    SELF(Actor)->mirror     = 0;
    ACTOR_CLEAR_TINT();
    SELF(Actor)->header.mode = 1;
}
