#include "battle_03.h"

MATCH void func_801E3A44(void) {
    PartyMember* work;
    u8           count;

    Battle_IsEnemyBlocked();
    work         = SELF(PartyMember);
    count        = work->unk_09 - 1;
    work->unk_09 = count;
    if (count == 0) {
        if (BATTLE_IS_SCRIPTED()) {
            Battle_PlayEnemySE(*g_BattleCurrentEnemy->unk_E8);
        } else {
            SND_SEPlay((g_BattleCurrentEnemy->type * 2) | 0x600);
        }
        SELF(PartyMember)->header.step = SELF(PartyMember)->header.step + 1;
    }
}
