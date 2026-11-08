#include "battle_03.h"

MATCH void func_801D277C(void) {
    u32  index;
    u8   slot;
    u16  rank;
    u32  flags;
    u16* half_flags;

    Battle_BuildTurnOrder();
    index = 0;
    if ((g_BattleState & BATTLE_STATE_COMMAND_ARMED) == 0) {
        g_BattleMessageState = 2;
    }
    D_8014839F            = 2;
    D_8014837B            = 2;
    g_BattleEventSlots[0] = 0;
    for (; (index & BYTE_MASK) < BATTLE_PARTY_CHARACTERS_COUNT; index++) {
        slot = index;
        if ((Battle_SlotIsBlocked(slot) & BYTE_MASK) != 0) {
            continue;
        }
        if (g_BattlePartyBattlers[slot].u.turn.command.type != BATTLE_COMMAND_ITEM) {
            continue;
        }
        rank = g_BattlePartyBattlers[slot].u.turn.command.id;
        if ((rank >> 8) == 0) {
            continue;
        }
        flags = g_BattlePartyBattlers[slot].u.turn.damage_flags.value;
        if (!(flags & 0x4000)) {
            func_801DDE7C(D_80145FB2[slot * BATTLE_PARTY_STRIDE], rank);
        } else {
            g_BattlePartyBattlers[slot].u.turn.damage_flags.value = flags & ~0x4000;
        }
    }
    half_flags = &g_BattleState;
    *half_flags |= 8;
    func_8009BFC4();
    if ((*half_flags & BATTLE_STATE_COMMAND_ARMED) == 0) {
        EMI_LoaderStreamInitSlot(EMI_SLOT_BATL_SE);
    }
    g_BattleStep += 1;
}
