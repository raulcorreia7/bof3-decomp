#include "boss036_16.h"

MATCH void func_800C1980(void) {
    PartyMember* work;

    if (--TASK(PartyMember)->unk_09 == 0) {
        Battle_PlayEnemySE(*g_BattleCurrentEnemy->unk_E8);
    }
    TASK(PartyMember)->pos.x.fixed += TASK(PartyMember)->unk_0C;
    if (TASK(PartyMember)->pos.x.fixed == TASK(PartyMember)->unk_18) {
        Battle_MarkDamaged(g_Battle.target_selector);
        Battle_TriggerCritical();
        work = TASK(PartyMember);
        work->header.mode++;
        work->unk_18 -= 0x30000;
        TASK(PartyMember)->header.step = 0;
    }
    Battle_IsEnemyBlocked();
}
