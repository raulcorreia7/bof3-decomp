#include "battle_03.h"

MATCH void func_801E4B2C(void) {
    PartyMember* work;

    if (EMI_IsReady() != 0) {
        if (((EnemyBattler*)g_BattleCurrentEnemy)->turn.command.type == BATTLE_COMMAND_ABILITY) {
            if (BATTLE_IS_SCRIPTED()) {
                if (!(func_801DDF50((((EnemyBattler*)g_BattleCurrentEnemy)->unk_F0 + 0x20) & BYTE_MASK, D_801463CD) & BYTE_MASK)) {
                    g_Task->unk_09 = 0x1EU;
                } else {
                    /* Shared zero store: blocked ability or non-4 state. */
                    goto block_5;
                }
            }
        } else {
        block_5:
            g_Task->unk_09 = 0U;
        }
        if (!(D_801CA71C[g_Battle.action_id].mask & 0x800)) {
            g_Task->unk_09 = MEM_PTR(u8, 0x800E40CFu)[((EnemyBattler*)g_BattleCurrentEnemy)->kind * 0x88u];
            func_801E2314(6U);
            work              = g_Task;
            work->header.step = (work->header.step + 1);
        } else {
            g_Task->header.mode = (g_Task->header.mode + 1);
        }
        Battle_IsEnemyBlockedOnce();
    }
}
