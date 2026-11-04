#include "battle_15.h"

MATCH void func_800A85A8(void) {
    PartyBattler* work;

    work         = (PartyBattler*)g_SpadWork;
    work->unk_20 = work->word_3C.word + 0x04000000;
    Actor_SelectScript((work->word_08.byte.unk_08 + 0x38) & BYTE_MASK);
    BATTLE_WORK->word_08.byte.unk_0B = 0x10;
    BATTLE_WORK->step_01++;
}
