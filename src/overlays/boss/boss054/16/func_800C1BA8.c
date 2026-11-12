#include "boss054_16.h"

MATCH void func_800C1BA8(void) {
    u32 slot;

    slot                               = Battle_AllocEffect(1, 93) & BYTE_MASK;
    g_BattleEffects[slot].target.party = g_Task;
    ((PartyMember*)g_Task)->timer += 1;
    ((PartyMember*)g_Task)->header.mode += 1;
}
