#include "battle_03.h"

MATCH void func_801E4A50(void) {
    if ((g_BattleCurrentEnemy->status & STATUS_KO) != 0u) {
        SELF(PartyMember)->header.mode = 6;
        SELF(PartyMember)->header.step = 4;
    } else {
        Battle_ClearSlotPending(SELF(PartyMember)->slot);
        SELF(PartyMember)->header.mode = 2;
        SELF(PartyMember)->header.step = 0;
    }
    SELF(PartyMember)->unk_03 = 0;
}
