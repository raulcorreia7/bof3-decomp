#include "boss036_16.h"

MATCH void func_800C1980(void) {
    PartyMember* work;

    if (--SELF(PartyMember)->unk_09 == 0) {
        Battle_PlayEnemySE(*g_BattleCurrentEnemy->unk_E8);
    }
    SELF(PartyMember)->pos.x.fixed += SELF(PartyMember)->unk_0C;
    if (SELF(PartyMember)->pos.x.fixed == SELF(PartyMember)->unk_18) {
        Battle_MarkDamaged(g_Battle.target_selector);
        Battle_TriggerCritical();
        work = SELF(PartyMember);
        work->header.mode++;
        work->unk_18 -= 0x30000;
        SELF(PartyMember)->header.step = 0;
    }
    Battle_IsEnemyBlocked();
}
