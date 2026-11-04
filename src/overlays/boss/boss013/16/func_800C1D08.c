#include "boss013_16.h"

MATCH void func_800C1D08(void) {
    EnemyBattler* work;

    work                            = g_BattleCurrentEnemy;
    work->script                    = D_800C25F0;
    work->unk_E4                    = func_800C1E58;
    work->unk_E8                    = D_800C2618;
    g_SpadWork->word_08.byte.unk_08 = 1;
    g_SpadWork->step_01             = 2;
}
