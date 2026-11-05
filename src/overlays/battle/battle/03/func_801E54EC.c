#include "battle_03.h"

extern volatile s32 D_8014632C;

MATCH void func_801E54EC(void) {
    u8            count;
    int           new_var;
    volatile s32* acc;

    g_Task->flags = g_Task->flags | ACTOR_FLAG_HIDDEN;
    acc           = &D_8014632C;
    *acc += g_BattleCurrentEnemy->exp;
    ORDER_LOCK_BEGIN
        D_80146330 += g_BattleCurrentEnemy->zenny;
        g_BattleCurrentEnemy->status |= STATUS_KO;
        g_BattleCurrentEnemy->zenny = 0;
        func_801DD14C(g_Task->slot);
        func_801E531C();
        count      = D_801462F3 - 1;
        D_801462F3 = count;
        new_var    = count == 0;
        if (new_var) {
            g_BattleResult |= BATTLE_RESULT_VICTORY;
        }
        if (((g_BattleState & BATTLE_STATE_OVER) != 0) && (D_801463CA == g_Task->slot)) {
            g_BattleState &= ~BATTLE_STATE_OVER;
        }
        func_800AD074(g_BattleCurrentEnemy->enemy_id.byte.kind);
        GFX_FreePaletteFadeTarget(g_Task);
        g_BattleCurrentEnemy->damage_flags &= ~0x70;
        Battle_ClearSlotPending(g_Task->slot);
        g_Task->mode = 2;
        g_Task->step = 0;
    ORDER_LOCK_END;
    g_Task->unk_03 = 0;
}
