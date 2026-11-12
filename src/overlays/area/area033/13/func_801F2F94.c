#include "area033_13.h"

/* Each access reloads the work cell through g_Task. */
MATCH void func_801F2F94(void) {
    g_Task->active_flags = 0x80;
    Area_SelectSceneRecord(0xF);
    g_Task->draw_layer = 5;
    g_Task->unk_2A     = 0;
    ACTOR_CLEAR_TINT();
    g_Task->header.mode = 1;
}
