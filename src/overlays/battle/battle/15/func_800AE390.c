#include "battle_15.h"

MATCH void func_800AE390(void) {
    PartyBattler* work;

    BATTLE_WORK->unk_09 = 0;
    work                = (PartyBattler*)g_Task;
    work->mode          = (u8)(work->mode + 1);
}
