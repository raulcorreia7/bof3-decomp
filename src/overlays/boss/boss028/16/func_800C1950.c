#include "boss028_16.h"
#include "area/spad.h"

MATCH void func_800C1950(void) {
    u8 timer;
    u8 index;

    timer                           = ((PartyMember*)g_Task)->unk_09 - 1;
    ((PartyMember*)g_Task)->unk_09 = timer;
    if (!timer) {
        Battle_PlayEnemyCue(*g_BattleCurrentEnemy->unk_E8);
    }
    if (func_801E30F8() != 0) {
        index                               = Battle_AllocEffect(3, 2) & BYTE_MASK;
        g_BattleEffects[index].header.mode  = 0;
        g_BattleEffects[index].target.party = (PartyMember*)g_Task;
        g_Task->header.step += 1;
    }
}
