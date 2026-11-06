#include "boss054_16.h"

MATCH void func_800C1BA8(void) {
    u32 offset;

    offset                                   = (Battle_AllocEffect(1, 0x5D) & BYTE_MASK) * BATTLE_EFFECT_STRIDE;
    FIELD(PartyBattler*, D_801EC3A4, offset) = g_Task;
    ((PartyBattler*)g_Task)->timer += 1;
    ((PartyBattler*)g_Task)->header.mode += 1;
}
