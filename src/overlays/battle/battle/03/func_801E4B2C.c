#include "battle_03.h"

MATCH void func_801E4B2C(void) {
    PartyBattler* work;

    if (EMI_LoaderIsReady() != 0) {
        if (((EnemyBattler*)g_BattleCurrentEnemy)->unk_F5 == 4) {
            if (g_BattleEncounter != 0) {
                if (!(func_801DDF50((((EnemyBattler*)g_BattleCurrentEnemy)->unk_F0 + 0x20) & BYTE_MASK,
                                    (u32)D_801463CD) &
                      0xFF)) {
                    g_SpadWork->word_08.byte.unk_09 = 0x1EU;
                } else {
                    /* Shared zero store: blocked ability or non-4 state. */
                    goto block_5;
                }
            }
        } else {
        block_5:
            g_SpadWork->word_08.byte.unk_09 = 0U;
        }
        if (!(D_801CA71C[g_BattleActionId].mask & 0x800)) {
            g_SpadWork->word_08.byte.unk_09 =
                MEM_PTR(u8, 0x800E40CFu)[((EnemyBattler*)g_BattleCurrentEnemy)->kind * 0x88u];
            func_801E2314(6U);
            work         = g_SpadWork;
            work->unk_02 = (u8)(work->unk_02 + 1);
        } else {
            g_SpadWork->step_01 = (u8)(g_SpadWork->step_01 + 1);
        }
        func_801E3160();
    }
}
