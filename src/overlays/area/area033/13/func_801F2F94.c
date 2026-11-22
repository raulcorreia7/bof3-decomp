#include "area033_13.h"

/* Each access reloads the work cell through g_Task. */
MATCH void func_801F2F94(void) {
    TASK(Actor)->active_flags = 0x80;
    Area_SceneSelectRecord(0xF);
    TASK(Actor)->draw_layer = 5;
    TASK(Actor)->mirror     = 0;
    ACTOR_CLEAR_TINT();
    TASK(Actor)->header.mode = 1;
}
