#include "battle_03.h"

MATCH void func_801E4B2C(void) {
    PartyMember* work;

    if (EMI_IsReady() != 0) {
        if (((EnemyBattler*)g_BattleCurrentEnemy)->turn.command.type == BATTLE_COMMAND_ABILITY) {
            if (BATTLE_IS_SCRIPTED()) {
                if (!(func_801DDF50((((EnemyBattler*)g_BattleCurrentEnemy)->unk_F0 + 0x20) & BYTE_MASK, g_Battle.unk_EA[3]) & BYTE_MASK)) {
                    SELF(PartyMember)->unk_09 = 0x1EU;
                } else {
                    /* Shared zero store: blocked ability or non-4 state. */
                    goto block_5;
                }
            }
        } else {
        block_5:
            SELF(PartyMember)->unk_09 = 0U;
        }
        if (!(D_801CA71C[g_Battle.action_id].mask & 0x800)) {
            SELF(PartyMember)->unk_09 = MEM_PTR(u8, 0x800E40CFu)[((EnemyBattler*)g_BattleCurrentEnemy)->type * 0x88u];
            Battle_RequestEnemyScript(6U);
            work              = SELF(PartyMember);
            work->header.step = (work->header.step + 1);
        } else {
            SELF(PartyMember)->header.mode = (SELF(PartyMember)->header.mode + 1);
        }
        Battle_IsEnemyBlockedOnce();
    }
}
