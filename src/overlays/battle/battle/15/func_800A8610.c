#include "battle_15.h"

MATCH void func_800A8610(void) {
    if (func_801DEE4C() & BYTE_MASK) {
        Actor_SelectScript((BATTLE_WORK->word_08.byte.unk_08 + 0x3C) & BYTE_MASK);
        BATTLE_WORK->step_01++;
    }
}
