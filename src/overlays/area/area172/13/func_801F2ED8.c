#include "area172_13.h"

MATCH void func_801F2ED8(void) {
    Actor* saved;
    u8     i;

    saved = g_Task;
    for (i = 0; i < 6; i++) {
        g_Task             = &g_Actors[i];
        g_Task->draw_layer = 2;
        func_8014D290();
    }
    for (i = 0; i < g_PartySize; i++) {
        if (g_Game.members[i].chr.character_id == CHAR_ID_RYU_ADULT) {
            TASK_SET(&g_Game.members[i]);
            g_Task->draw_layer = 2;
            func_8014D290();
        }
    }
    g_Task = saved;
}
