#include "battle_03.h"

MATCH void func_801E3A44(void) {
    PartyMember* work;
    u8           count;

    func_801E30F8();
    work         = g_Task;
    count        = work->unk_09 - 1;
    work->unk_09 = count;
    if (count == 0) {
        if (g_Battle.encounter != 0) {
            func_801E52F0(*g_BattleCurrentEnemy->unk_E8);
        } else {
            SND_PlayCue((g_BattleCurrentEnemy->kind * 2) | 0x600);
        }
        g_Task->header.step = g_Task->header.step + 1;
    }
}
