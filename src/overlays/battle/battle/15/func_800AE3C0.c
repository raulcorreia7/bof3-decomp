#include "battle_15.h"

MATCH void func_800AE3C0(void) {
    PartyBattler* work;
    s8            counter;

    work                      = (PartyBattler*)g_SpadWork;
    counter                   = work->word_08.byte.unk_09 - 1;
    work->word_08.byte.unk_09 = counter;
    if (counter == -6) {
        BATTLE_WORK->step_01++;
    }
    Area_UpdatePaletteTint((s8)BATTLE_WORK->word_08.byte.unk_09);
}
