#include "boss033_16.h"

MATCH void func_800C1A58(void) {
    u8 timer;

    timer                         = ((PartyMember*)g_Task)->timer - 1;
    ((PartyMember*)g_Task)->timer = timer;
    if (!(timer & BYTE_MASK)) {
        Battle_PlayEnemyCue(*g_BattleCurrentEnemy->unk_E8);
        Battle_PlayEnemyCue((*g_BattleCurrentEnemy->unk_E8 + 4) & HALF_MASK);
        ((PartyMember*)g_Task)->header.step += 1;
    }
}
