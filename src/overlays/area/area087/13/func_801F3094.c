#include "area087_13.h"

MATCH void func_801F3094(void) {
    TASK(Actor)->active_flags = 0x80;
    Area_SceneSelectRecord(0x156);
    TASK(Actor)->draw_layer = 5;
    TASK(Actor)->mirror     = 0;
    ACTOR_CLEAR_TINT();
    TASK(Actor)->header.mode = 1;
}
