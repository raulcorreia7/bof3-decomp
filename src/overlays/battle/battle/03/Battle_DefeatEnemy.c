#include "battle_03.h"

/* func_801E54EC */
MATCH void Battle_DefeatEnemy(void) {
    u8            count;
    int           new_var;
    volatile u32* acc;

    BATTLE_WORK->header.flags = BATTLE_WORK->header.flags | ACTOR_FLAG_HIDDEN;
    acc                       = &g_Battle.outcome.reward_exp;
    *acc += g_BattleCurrentEnemy->exp;
    FAKE_ORDER_LOCK_BEGIN
        g_Battle.outcome.reward_zenny += g_BattleCurrentEnemy->zenny;
        g_BattleCurrentEnemy->status |= STATUS_KO;
        g_BattleCurrentEnemy->zenny = 0;
        Battle_CancelTurn(BATTLE_WORK->slot);
        Battle_RollEnemyDrops();
        count                       = g_Battle.living_enemy_count - 1;
        g_Battle.living_enemy_count = count;
        new_var                     = count == 0;
        if (new_var) {
            g_Battle.outcome.result |= BATTLE_RESULT_VICTORY;
        }
        if (((g_Battle.flags & BATTLE_STATE_OVER) != 0) && (D_801463CA == BATTLE_WORK->slot)) {
            g_Battle.flags &= ~BATTLE_STATE_OVER;
        }
        func_800AD074(g_BattleCurrentEnemy->enemy_id.byte.type);
        GFX_PaletteFreeFadeTarget(g_Task);
        g_BattleCurrentEnemy->turn.damage_flags.value &= ~(BATTLER_DAMAGE_UNK_4 | BATTLER_DAMAGE_UNK_5 | BATTLER_DAMAGE_TAKEN);
        Battle_ClearSlotPending(BATTLE_WORK->slot);
        BATTLE_WORK->header.mode = 2;
        BATTLE_WORK->header.step = 0;
    FAKE_ORDER_LOCK_END;
    BATTLE_WORK->unk_03 = 0;
}
