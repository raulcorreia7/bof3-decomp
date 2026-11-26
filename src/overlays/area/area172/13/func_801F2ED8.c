#include "area172_13.h"

MATCH void func_801F2ED8(void) {
    Actor* saved;
    u8     i;

    saved = SELF(Actor);
    for (i = 0; i < 6; i++) {
        g_Self                  = &g_Actors[i];
        SELF(Actor)->draw_layer = 2;
        Area_AddGridActor();
    }
    for (i = 0; i < g_PartySize; i++) {
        if (g_Game.members[i].chr.character_id == CHAR_ID_RYU_ADULT) {
            SELF_SET(&g_Game.members[i]);
            SELF(Actor)->draw_layer = 2;
            Area_AddGridActor();
        }
    }
    g_Self = saved;
}
