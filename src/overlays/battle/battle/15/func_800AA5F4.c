#include "battle_15.h"

MATCH s32 func_800AA5F4(s32 slot) {
    s32 record;

    slot &= BYTE_MASK;
    if (Battle_SlotIsBlocked(slot) & BYTE_MASK) {
        return 0;
    }
    record = slot * BATTLE_PARTY_STRIDE;
    if (!(g_BattlePartyBattlers[slot].damage_flags.volatile_value & 1)) {
        return 0;
    }
    if (g_BattlePartyBattlers[slot].unk_118 != LOBU(g_BattleActiveBattler)) {
        return 0;
    }
    if (func_800AA874(*(u8*)&g_BattleAction->unk_02) & BYTE_MASK) {
        return 0;
    }
    if (func_800AA8A4(slot) & BYTE_MASK) {
        return 0;
    }
    if (g_CharSlot[D_80145F09[record]] != 6) {
        slot = D_800B50DC[D_801CA719[g_BattleAction->unk_02 * 0x14] >> 4];
    } else {
        slot = D_800B50E4[D_801CA719[g_BattleAction->unk_02 * 0x14] >> 4];
    }
    return ((rand() % slot) & BYTE_MASK) == 0;
}
