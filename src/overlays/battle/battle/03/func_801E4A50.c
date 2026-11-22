#include "battle_03.h"

MATCH void func_801E4A50(void) {
    if ((g_BattleCurrentEnemy->status & STATUS_KO) != 0u) {
        TASK(PartyMember)->header.mode = 6;
        TASK(PartyMember)->header.step = 4;
    } else {
        Battle_ClearSlotPending(TASK(PartyMember)->slot);
        TASK(PartyMember)->header.mode = 2;
        TASK(PartyMember)->header.step = 0;
    }
    TASK(PartyMember)->unk_03 = 0;
}
