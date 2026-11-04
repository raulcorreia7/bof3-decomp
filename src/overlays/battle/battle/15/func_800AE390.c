#include "battle_15.h"

MATCH void func_800AE390(void) {
    PartyBattler* work;

    BATTLE_WORK->word_08.byte.unk_09 = 0;
    work                             = (PartyBattler*)g_SpadWork;
    work->step_01                    = (u8)(work->step_01 + 1);
}
