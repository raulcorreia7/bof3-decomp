/* Initialises the area work bytes and loads scene 0x1D1. */
/* func_801F2F24 (area152), func_801F2FD0 (area151) */
#include "area/spad.h"

MATCH void WorldMap_StartScene(void) {
    g_Task->active_flags = 0x80;
    Area_SelectSceneRecord(0x1D1);
    g_Task->draw_layer = 5;
    g_Task->unk_2A     = 0;
    ACTOR_CLEAR_TINT();
    g_Task->header.mode = 1;
}
