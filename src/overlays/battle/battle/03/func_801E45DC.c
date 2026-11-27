#include "battle_03.h"

MATCH void func_801E45DC(void) {
    PartyMember* work;
    u32          slot;
    u8           count;

    work        = SELF(PartyMember);
    count       = work->timer - 1;
    work->timer = count;
    if (count == 0) {
        if ((g_BattleCurrentEnemy->turn.target_flags & BATTLE_HIT_HP_LANDED) != 0) {
            Battle_QueueAction(g_BattleCurrentEnemy->turn.hp_change, SELF(PartyMember)->slot);
        } else {
            slot                               = Battle_AllocEffect(0, 1) & BYTE_MASK;
            g_BattleEffects[slot].target.party = SELF(PartyMember);
            g_BattleEffects[slot].unk_07       = 3;
            g_BattleEffects[slot].unk_27       = 0;
        }
        SELF(PartyMember)->unk_03 = SELF(PartyMember)->unk_03 + 1;
    }
    SELF(PartyMember)->pos.x.fixed -= SELF(PartyMember)->unk_0C;
    SELF(PartyMember)->pos.y.fixed -= SELF(PartyMember)->unk_10;
    Battle_IsEnemyBlocked();
}
