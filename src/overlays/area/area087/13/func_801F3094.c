#include "area087_13.h"

MATCH void func_801F3094(void) {
    g_Task->active_flags = 0x80;
    Area_SelectSceneRecord(0x156);
    g_Task->draw_layer = 5;
    g_Task->unk_2A     = 0;
    ACTOR_CLEAR_TINT();
    g_Task->header.mode = 1;
}
