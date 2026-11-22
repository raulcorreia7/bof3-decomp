#include "boss054_16.h"

MATCH void func_800C1D7C(void) {
    BossEffect054Steps handlers;

    handlers = D_800C182C;
    handlers.steps[TASK(PartyMember)->header.step]();
    if (ACTOR_IN_USE(*TASK(PartyMember))) {
        Script_AnimStepLoop();
        Area_AddGridActor();
    }
}
