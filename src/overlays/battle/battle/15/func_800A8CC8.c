#include "battle_15.h"

MATCH void func_800A8CC8(void) {
    Actor_SelectScript((BATTLE_WORK->word_08.byte.unk_08 + 0x50) & BYTE_MASK);
    func_801DEE4C();
    BATTLE_WORK->unk_29              = 3;
    BATTLE_WORK->word_08.byte.unk_09 = 8;
    BATTLE_WORK->step_01++;
}
