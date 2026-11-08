#include "battle_15.h"

MATCH s32 func_800AA5F4(s32 slot) {
    slot &= BYTE_MASK;
    if (Battle_SlotIsBlocked(slot) & BYTE_MASK) {
        return 0;
    }
    if (!(g_BattlePartyBattlers[slot].u.turn.damage_flags.volatile_value & COMBATANT_FLAG_COMMAND_ENTERED)) {
        return 0;
    }
    if (g_BattlePartyBattlers[slot].u.turn.command.target != LOBU(g_BattleActiveBattler)) {
        return 0;
    }
    if (func_800AA874(*(u8*)&g_BattleAction->unk_02) & BYTE_MASK) {
        return 0;
    }
    if (func_800AA8A4(slot) & BYTE_MASK) {
        return 0;
    }
    if (g_CharSlot[g_BattlePartyBattlers[slot].chr.character_id] != 6) {
        slot = D_800B50DC[D_801CA719[g_BattleAction->unk_02 * 0x14] >> 4];
    } else {
        slot = D_800B50E4[D_801CA719[g_BattleAction->unk_02 * 0x14] >> 4];
    }
    return ((rand() % slot) & BYTE_MASK) == 0;
}
