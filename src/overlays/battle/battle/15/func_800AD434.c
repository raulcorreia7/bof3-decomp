#include "battle_15.h"

MATCH void func_800AD434(void) {
    PartyMember* work;
    Callback     funcs[2] = {func_800AD4D4, func_800AD5C8};
    u8           two;

    work = (PartyMember*)g_Task;
    funcs[work->header.step]();
    two = 2u;
    if (!(D_80148624 & 0x1)) {
        BATTLE_WORK->header.mode = two;
        BATTLE_WORK->header.step = 0;
        return;
    }
    Actor_StepAnimLoop();
    Area_AddActor();
}
