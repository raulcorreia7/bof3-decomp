#include "area115_13.h"

/* Each access reloads the work cell: the stores go through its pointer, which
 * the compiler must assume may alias the cell. */

MATCH void func_801F3064(void) {
    g_Task->active_flags = 0x80;
    Area_SelectSceneRecord(0x1C7);
    g_Task->draw_layer = 5;
    g_Task->unk_2A     = 0;
    ACTOR_CLEAR_TINT();
    g_Task->header.mode = 1;
}
