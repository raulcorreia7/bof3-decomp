#include "battle_03.h"

MATCH void func_801E4C7C(void) {
    PartyMember* work;
    u8           count;

    work  = SELF(PartyMember);
    count = work->unk_09;
    if (count == 0) {
        if (BATTLE_IS_SCRIPTED()) {
            Battle_PlayEnemySE(g_BattleCurrentEnemy->unk_E8[1]);
        } else {
            SND_SEPlay((g_BattleCurrentEnemy->type * 2) | 0x601);
        }
        work              = SELF(PartyMember);
        work->header.step = work->header.step + 1;
    } else {
        work->unk_09 = count - 1;
    }
    Battle_IsEnemyBlockedOnce();
}
