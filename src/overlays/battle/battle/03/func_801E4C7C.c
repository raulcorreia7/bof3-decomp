#include "battle_03.h"

MATCH void func_801E4C7C(void) {
    PartyMember* work;
    u8           count;

    work  = g_Task;
    count = work->unk_09;
    if (count == 0) {
        if (BATTLE_IS_SCRIPTED()) {
            Battle_PlayEnemyCue(g_BattleCurrentEnemy->unk_E8[1]);
        } else {
            SND_PlayCue((g_BattleCurrentEnemy->kind * 2) | 0x601);
        }
        work              = g_Task;
        work->header.step = work->header.step + 1;
    } else {
        work->unk_09 = count - 1;
    }
    Battle_IsEnemyBlockedOnce();
}
