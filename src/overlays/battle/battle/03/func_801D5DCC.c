#include "battle_03.h"

/* sums the per-turn hit point change of each living party member (modes, equipment, accessories, status bit 1)
 * and arms the follow-up state for every battler whose change is non-zero; living enemies with status bit 1 take half
 * of their max HP. Returns whether D_801463C2 is set.
 */
MATCH u8 func_801D5DCC(void) {
    u8  slot;
    s16 delta;

    for (slot = 0; slot < BATTLE_PARTY_SLOT_COUNT; slot++) {
        if (!(func_801D64C4(slot) & BYTE_MASK)) {
            g_BattlePartyBattlers[slot].hp_change = 0;
            g_BattlePartyBattlers[slot].ap_change = 0;
            /* FAKE: keeps the mode byte load after the two stores (the scheduler hoists it above them). */
            MATCH_BARRIER();
            if (g_PartyFormation == 5) {
                g_BattlePartyBattlers[slot].hp_change -= 1;
            }
            if (g_BattlePartyBattlers[slot].chr.character_id == CHAR_ID_PECO) {
                g_BattlePartyBattlers[slot].hp_change -= (g_BattlePartyBattlers[slot].chr.stats.max_hp + 10) / 20;
            }
            if (g_BattlePartyBattlers[slot].chr.character_id == CHAR_ID_RYU_ADULT ||
                g_BattlePartyBattlers[slot].chr.character_id == CHAR_ID_RYU_YOUNG) {
                if (g_BattlePartyBattlers[slot].action_flags.volatile_value & 2) {
                    if (g_DragonForm == 0x12) {
                        g_BattlePartyBattlers[slot].hp_change -=
                            (g_BattlePartyBattlers[slot].chr.stats.max_hp + 10) / 20;
                    }
                }
            }
            if (g_BattlePartyBattlers[slot].chr.equip.weapon == WEAPON_BEAST_SPEAR) {
                delta =
                    g_BattlePartyBattlers[slot].hp_change + (g_BattlePartyBattlers[slot].chr.stats.max_hp + 10) / 20;
                g_BattlePartyBattlers[slot].hp_change = delta;
                if (delta >= g_BattlePartyBattlers[slot].chr.hp) {
                    g_BattlePartyBattlers[slot].hp_change = g_BattlePartyBattlers[slot].chr.hp - 1;
                }
            }
            if (g_BattlePartyBattlers[slot].chr.equip.armor == ARMOR_LIFE_ARMOR) {
                g_BattlePartyBattlers[slot].hp_change -= 1;
            }
            if (g_BattlePartyBattlers[slot].chr.equip.accessories[0] == ACCESSORY_CUPIDS_LYRE) {
                g_BattlePartyBattlers[slot].hp_change -= 1;
            }
            if (g_BattlePartyBattlers[slot].chr.equip.accessories[1] == ACCESSORY_CUPIDS_LYRE) {
                g_BattlePartyBattlers[slot].hp_change -= 1;
            }
            if (g_BattlePartyBattlers[slot].chr.equip.accessories[0] == ACCESSORY_IVORY_CHARM) {
                g_BattlePartyBattlers[slot].hp_change -= 1;
            }
            if (g_BattlePartyBattlers[slot].chr.equip.accessories[1] == ACCESSORY_IVORY_CHARM) {
                g_BattlePartyBattlers[slot].hp_change -= 1;
            }
            if (HAS_STATUS(g_BattlePartyBattlers[slot], 1)) {
                g_BattlePartyBattlers[slot].hp_change -= g_BattlePartyBattlers[slot].chr.stats.max_hp >> 1;
            }
            if ((s16)g_BattlePartyBattlers[slot].hp_change != 0) {
                g_BattlePartyBattlers[slot].mode    = 6;
                g_BattlePartyBattlers[slot].step    = 5;
                g_BattlePartyBattlers[slot].unk_04  = 0;
                g_BattlePartyBattlers[slot].unk_03  = 0;
                g_BattlePartyBattlers[slot].unk_120 = 0x11;
                Battle_SetSlotPending(slot);
            }
        }
    }
    for (slot = 3; slot < COMBATANT_COUNT; slot++) {
        if (!(func_801D64C4(slot) & BYTE_MASK)) {
            if (ENEMY_COMBATANT(slot).status & 1) {
                ENEMY_COMBATANT(slot).mode         = 6;
                ENEMY_COMBATANT(slot).step         = 5;
                ENEMY_COMBATANT(slot).unk_04       = 0;
                ENEMY_COMBATANT(slot).unk_03       = 0;
                ENEMY_COMBATANT(slot).target_flags = 0x11;
                ENEMY_COMBATANT(slot).hp_change    = -(ENEMY_COMBATANT(slot).stats.max_hp >> 1);
                Battle_SetSlotPending(slot);
            }
        }
    }
    return D_801463C2 != 0;
}
