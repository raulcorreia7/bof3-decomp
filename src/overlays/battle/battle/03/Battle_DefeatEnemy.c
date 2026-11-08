#include "battle_03.h"

/* func_801E54EC */
MATCH void Battle_DefeatEnemy(void) {
    u8            count;
    int           new_var;
    volatile u32* acc;

    g_Task->header.flags = g_Task->header.flags | ACTOR_FLAG_HIDDEN;
    acc                  = &g_BattleOutcome.reward_exp;
    *acc += g_BattleCurrentEnemy->exp;
    ORDER_LOCK_BEGIN
        g_BattleOutcome.reward_zenny += g_BattleCurrentEnemy->zenny;
        g_BattleCurrentEnemy->status |= STATUS_KO;
        g_BattleCurrentEnemy->zenny = 0;
        Battle_CancelTurn(g_Task->slot);
        Battle_RollEnemyDrops();
        count                    = g_BattleLivingEnemyCount - 1;
        g_BattleLivingEnemyCount = count;
        new_var                  = count == 0;
        if (new_var) {
            g_BattleOutcome.result |= BATTLE_RESULT_VICTORY;
        }
        if (((g_BattleState & BATTLE_STATE_OVER) != 0) && (D_801463CA == g_Task->slot)) {
            g_BattleState &= ~BATTLE_STATE_OVER;
        }
        func_800AD074(g_BattleCurrentEnemy->enemy_id.byte.kind);
        GFX_FreePaletteFadeTarget(g_Task);
        g_BattleCurrentEnemy->turn.damage_flags.value &=
            ~(COMBATANT_FLAG_UNK_4 | COMBATANT_FLAG_UNK_5 | COMBATANT_FLAG_DAMAGED);
        Battle_ClearSlotPending(g_Task->slot);
        g_Task->header.mode = 2;
        g_Task->header.step = 0;
    ORDER_LOCK_END;
    g_Task->unk_03 = 0;
}
