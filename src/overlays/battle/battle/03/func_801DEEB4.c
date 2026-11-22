#include "battle_03.h"

MATCH void func_801DEEB4(void) {
    volatile PartyMember* work = TASK(PartyMember);

    if (ACTOR_IN_USE(*work)) {
        D_801EB120[work->header.mode]();
    }
}
