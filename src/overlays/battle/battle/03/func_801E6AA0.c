#include "battle_03.h"

MATCH void func_801E6AA0(void) {
    BattleEffect2Steps handlers;

    handlers = D_801D0F38;
    handlers.steps[SELF(PartyMember)->header.mode]();
    if (ACTOR_IN_USE(*SELF(PartyMember))) {
        Area_AddActor();
    }
}
