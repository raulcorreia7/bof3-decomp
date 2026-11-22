#include "battle_03.h"

MATCH void func_801E45DC(void) {
    PartyMember* work;
    u32          slot;
    u8           count;

    work        = TASK(PartyMember);
    count       = work->timer - 1;
    work->timer = count;
    if (count == 0) {
        if ((g_BattleCurrentEnemy->turn.target_flags & BATTLE_HIT_HP_LANDED) != 0) {
            Battle_QueueAction(g_BattleCurrentEnemy->turn.hp_change, TASK(PartyMember)->slot);
        } else {
            slot                               = Battle_AllocEffect(0, 1) & BYTE_MASK;
            g_BattleEffects[slot].target.party = TASK(PartyMember);
            g_BattleEffects[slot].unk_07       = 3;
            g_BattleEffects[slot].unk_27       = 0;
        }
        TASK(PartyMember)->unk_03 = TASK(PartyMember)->unk_03 + 1;
    }
    TASK(PartyMember)->pos.x.fixed -= TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->pos.y.fixed -= TASK(PartyMember)->unk_10;
    Battle_IsEnemyBlocked();
}
