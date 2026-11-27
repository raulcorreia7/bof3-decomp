#include "battle_15.h"

MATCH void func_800AD434(void) {
    PartyMember* work;
    Callback     funcs[2] = {func_800AD4D4, func_800AD5C8};
    u8           two;

    work = SELF(PartyMember);
    funcs[work->header.step]();
    two = 2u;
    if (!(g_UiPanelTasks[21].active & 0x1)) {
        SELF(PartyMember)->header.mode = two;
        SELF(PartyMember)->header.step = 0;
        return;
    }
    Script_AnimStepLoop();
    Area_AddActor();
}
