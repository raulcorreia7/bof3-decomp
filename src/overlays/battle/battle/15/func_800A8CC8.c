#include "battle_15.h"

MATCH void func_800A8CC8(void) {
    Actor_SelectScript((BATTLE_WORK->facing + 0x50) & 0xFF);
    func_801DEE4C();
    BATTLE_WORK->unk_29 = 3;
    BATTLE_WORK->unk_09 = 8;
    BATTLE_WORK->header.mode++;
}
