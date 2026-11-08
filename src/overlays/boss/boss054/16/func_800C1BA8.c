#include "boss054_16.h"

MATCH void func_800C1BA8(void) {
    u32 slot;

    slot                               = Battle_AllocEffect(1, 0x5D) & BYTE_MASK;
    g_BattleEffects[slot].target.party = g_Task;
    ((PartyBattler*)g_Task)->timer += 1;
    ((PartyBattler*)g_Task)->header.mode += 1;
}
