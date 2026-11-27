#include "area065_13.h"

/* Each access reloads the work cell: the stores go through its pointer, which
 * the compiler must assume may alias the cell. */

MATCH void func_801F3098(void) {
    SELF(Actor)->active_flags = 0x80;
    Area_SceneSelectRecord(0x53);
    SELF(Actor)->draw_layer = 5;
    SELF(Actor)->mirror     = 0;
    ACTOR_CLEAR_TINT();
    SELF(Actor)->header.mode = 1;
}
