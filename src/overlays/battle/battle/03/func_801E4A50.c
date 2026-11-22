#include "battle_03.h"

MATCH void func_801E4A50(void) {
    if ((g_BattleCurrentEnemy->status & STATUS_KO) != 0u) {
        BATTLE_WORK->header.mode = 6;
        BATTLE_WORK->header.step = 4;
    } else {
        Battle_ClearSlotPending(BATTLE_WORK->slot);
        BATTLE_WORK->header.mode = 2;
        BATTLE_WORK->header.step = 0;
    }
    BATTLE_WORK->unk_03 = 0;
}
