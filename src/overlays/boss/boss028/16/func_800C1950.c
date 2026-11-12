#include "boss028_16.h"
#include "area/spad.h"

MATCH void func_800C1950(void) {
    u8 timer;
    u8 index;

    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (!(timer & BYTE_MASK)) {
        Battle_PlayEnemyCue(*g_BattleCurrentEnemy->unk_E8);
    }
    if (func_801E30F8() & BYTE_MASK) {
        index                               = Battle_AllocEffect(3, 2) & BYTE_MASK;
        g_BattleEffects[index].header.mode  = 0;
        g_BattleEffects[index].target.party = (PartyMember*)g_Task;
        g_Task->header.step += 1;
    }
}
