#include "battle_15.h"

MATCH void func_800A9610(u8 selector, u16 flags) {
    s32 i;
    u8  slot;
    s32 battler;
    s32 player_flags;
    s32 enemy_flags;

    if (selector & 0xC0) {
        if (selector & 0x80) {
            i            = 0;
            player_flags = flags;
            do {
                slot = i & BYTE_MASK;
                if (!Battle_SlotIsBlocked(slot)) {
                    s32 offset;

                    offset             = slot * BATTLE_PARTY_STRIDE;
                    D_80145E91[offset] = 0xB;
                    g_BattlePartyBattlers[slot].damage_flags.volatile_value |= player_flags;
                    Battle_SetSlotPending(slot);
                }
                i++;
            } while ((u32)(i & BYTE_MASK) < BATTLE_PARTY_SLOT_COUNT);
        }
        if (selector & 0x40) {
            i           = BATTLE_PARTY_SLOT_COUNT;
            enemy_flags = flags;
            do {
                slot = i & BYTE_MASK;
                if (!Battle_SlotIsBlocked(slot)) {
                    s32 offset;

                    offset             = (slot - BATTLE_PARTY_SLOT_COUNT) * BATTLE_ENEMY_STRIDE;
                    D_801EB631[offset] = 0xB;
                    ENEMY_COMBATANT(slot).damage_flags |= enemy_flags;
                    Battle_SetSlotPending(slot);
                }
                i++;
            } while ((u32)(i & BYTE_MASK) < COMBATANT_COUNT);
        }
    } else {
        slot = selector & BYTE_MASK;
        if (!Battle_SlotIsBlocked(slot)) {
            if (slot < BATTLE_PARTY_SLOT_COUNT) {
                s32 offset;

                battler            = slot;
                offset             = battler * BATTLE_PARTY_STRIDE;
                D_80145E91[offset] = 0xB;
                g_BattlePartyBattlers[battler].damage_flags.volatile_value |= flags;
                Battle_SetSlotPending(battler);
            } else {
                s32 offset;

                battler            = slot;
                offset             = (battler - BATTLE_PARTY_SLOT_COUNT) * BATTLE_ENEMY_STRIDE;
                D_801EB631[offset] = 0xB;
                ENEMY_COMBATANT(battler).damage_flags |= flags;
                Battle_SetSlotPending(battler);
            }
        }
    }
}
