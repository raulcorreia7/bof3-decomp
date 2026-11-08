#include "boss051_16.h"
#include "game/enemy.h"
#include "overlays/battle/battle.h"

MATCH void func_800C1900(void) {
    u8           slot;
    PartyMember* work;

    g_Task->unk_09                     = ENCOUNTER_ENEMIES[g_BattleCurrentEnemy->kind].unk_84[2];
    slot                               = Battle_AllocEffect(3, 7);
    work                               = g_Task;
    g_BattleEffects[slot].target.party = work;
    work->header.step++;
}
