#include "area108_14.h"

MATCH void func_801F3C84(void) {
    PartyMember* saved;
    Actor*       actor;
    PartyMember* battler;
    u8           i;
    u8           j;

    saved = SELF(PartyMember);
    for (i = 0; i < ACTOR_COUNT; i++) {
        actor = &g_Actors[i];
        SELF_SET(actor);
        if (actor->header.flags & 0x1) {
            actor->draw_layer = 5;
            Area_AddGridActor();
        }
    }
    for (j = 0; j < g_PartySize; j++) {
        battler = &g_Game.members[j];
        SELF_SET(battler);
        battler->unk_29 = 5;
        Area_AddGridActor();
    }
    SELF_SET(saved);
}
