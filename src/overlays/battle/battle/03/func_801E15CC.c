#include "battle_03.h"

MATCH void func_801E15CC(void) {
    func_801DEDE4();
    if (HAS_STATUS(*g_Game.current, STATUS_KO)) {
        BATTLE_WORK->header.mode = 6;
        BATTLE_WORK->header.step = 4;
    } else {
        Battle_ClearSlotPending(BATTLE_WORK->slot);
        BATTLE_WORK->header.mode = 3;
        BATTLE_WORK->header.step = 0;
    }
    BATTLE_WORK->unk_03 = 0;
}
