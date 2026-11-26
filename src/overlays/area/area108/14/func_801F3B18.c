#include "area108_14.h"

MATCH void func_801F3B18(void) {
    Actor* saved = SELF(Actor);
    u8     i;

    for (i = 0; i < g_PartySize; i++) {
        SELF_SET(&g_Game.members[i]);
        SELF(Actor)->draw_layer = 6;
    }
    g_Self = saved;
    Actor_Clear();
}
