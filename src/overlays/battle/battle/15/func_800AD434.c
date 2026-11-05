#include "battle_15.h"

MATCH void func_800AD434(void) {
    PartyBattler* work;
    Callback      funcs[2] = {func_800AD4D4, func_800AD5C8};
    u8            two;

    work = (PartyBattler*)g_Task;
    funcs[work->step]();
    two = 2u;
    if (!(D_80148624 & 1)) {
        BATTLE_WORK->mode = two;
        BATTLE_WORK->step = 0;
        return;
    }
    func_8014D978();
    Area_AddActor();
}
