#include "battle_03.h"

MATCH void func_801E3A44(void) {
    PartyMember* work;
    u8           count;

    Battle_IsEnemyBlocked();
    work         = g_Task;
    count        = work->unk_09 - 1;
    work->unk_09 = count;
    if (count == 0) {
        if (BATTLE_IS_SCRIPTED()) {
            Battle_PlayEnemyCue(*g_BattleCurrentEnemy->unk_E8);
        } else {
            SND_PlayCue((g_BattleCurrentEnemy->kind * 2) | 0x600);
        }
        g_Task->header.step = g_Task->header.step + 1;
    }
}
