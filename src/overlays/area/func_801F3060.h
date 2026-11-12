/* Each access reloads the work cell: the stores go through its pointer, which
 * the compiler must assume may alias the cell. */
#include "area/spad.h"

MATCH void func_801F3060(void) {
    g_Task->active_flags = 0x80;
    Area_SelectSceneRecord(AREA_SCENE_RECORD);
    g_Task->draw_layer = 5;
    g_Task->unk_2A     = 0;
    ACTOR_CLEAR_TINT();
    g_Task->header.mode = 1;
}
