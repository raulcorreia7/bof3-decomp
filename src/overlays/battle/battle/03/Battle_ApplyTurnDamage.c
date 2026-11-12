#include "battle_03.h"

/* sums the per-turn hit point change of each living party member (modes, equipment, accessories, status bit 1)
 * and arms the follow-up state for every battler whose change is non-zero; living enemies with status bit 1 take half
 * of their max HP. Returns whether D_801463C2 is set.
 */
/* func_801D5DCC */
MATCH u8 Battle_ApplyTurnDamage(void) {
    u8  slot;
    s16 delta;

    for (slot = 0; slot < BATTLE_PARTY_CHARACTERS_COUNT; slot++) {
        if (!(func_801D64C4(slot) & BYTE_MASK)) {
            g_Game.members[slot].u.turn.hp_change = 0;
            g_Game.members[slot].u.turn.ap_change = 0;
            /* FAKE: keeps the mode byte load after the two stores (the scheduler hoists it above them). */
            FAKE_BARRIER();
            if (g_PartyFormation == 5) {
                g_Game.members[slot].u.turn.hp_change -= 1;
            }
            if (g_Game.members[slot].chr.character_id == CHAR_ID_PECO) {
                g_Game.members[slot].u.turn.hp_change -= (g_Game.members[slot].chr.stats.max_hp + 10) / 20;
            }
            if (g_Game.members[slot].chr.character_id == CHAR_ID_RYU_ADULT || g_Game.members[slot].chr.character_id == CHAR_ID_RYU_YOUNG) {
                if (g_Game.members[slot].u.turn.action_flags.volatile_value & COMBATANT_FLAG_DRAGON_FORM) {
                    if (g_Battle.dragon_form == 0x12) {
                        g_Game.members[slot].u.turn.hp_change -= (g_Game.members[slot].chr.stats.max_hp + 10) / 20;
                    }
                }
            }
            if (g_Game.members[slot].chr.equip.weapon == WEAPON_BEAST_SPEAR) {
                delta                                 = g_Game.members[slot].u.turn.hp_change + (g_Game.members[slot].chr.stats.max_hp + 10) / 20;
                g_Game.members[slot].u.turn.hp_change = delta;
                if (delta >= g_Game.members[slot].chr.hp) {
                    g_Game.members[slot].u.turn.hp_change = g_Game.members[slot].chr.hp - 1;
                }
            }
            if (g_Game.members[slot].chr.equip.armor == ARMOR_LIFE_ARMOR) {
                g_Game.members[slot].u.turn.hp_change -= 1;
            }
            if (g_Game.members[slot].chr.equip.accessories[0] == ACCESSORY_CUPIDS_LYRE) {
                g_Game.members[slot].u.turn.hp_change -= 1;
            }
            if (g_Game.members[slot].chr.equip.accessories[1] == ACCESSORY_CUPIDS_LYRE) {
                g_Game.members[slot].u.turn.hp_change -= 1;
            }
            if (g_Game.members[slot].chr.equip.accessories[0] == ACCESSORY_IVORY_CHARM) {
                g_Game.members[slot].u.turn.hp_change -= 1;
            }
            if (g_Game.members[slot].chr.equip.accessories[1] == ACCESSORY_IVORY_CHARM) {
                g_Game.members[slot].u.turn.hp_change -= 1;
            }
            if (HAS_STATUS(g_Game.members[slot], 1)) {
                g_Game.members[slot].u.turn.hp_change -= g_Game.members[slot].chr.stats.max_hp >> 1;
            }
            if ((s16)g_Game.members[slot].u.turn.hp_change != 0) {
                g_Game.members[slot].header.mode         = 6;
                g_Game.members[slot].header.step         = 5;
                g_Game.members[slot].unk_04              = 0;
                g_Game.members[slot].unk_03              = 0;
                g_Game.members[slot].u.turn.target_flags = 0x11;
                Battle_SetSlotPending(slot);
            }
        }
    }
    for (slot = 3; slot < COMBATANT_COUNT; slot++) {
        if (!(func_801D64C4(slot) & BYTE_MASK)) {
            if (ENEMY_COMBATANT(slot).status & STATUS_UNK_0) {
                ENEMY_COMBATANT(slot).header.mode       = 6;
                ENEMY_COMBATANT(slot).header.step       = 5;
                ENEMY_COMBATANT(slot).unk_04            = 0;
                ENEMY_COMBATANT(slot).unk_03            = 0;
                ENEMY_COMBATANT(slot).turn.target_flags = 0x11;
                ENEMY_COMBATANT(slot).turn.hp_change    = -(ENEMY_COMBATANT(slot).stats.max_hp >> 1);
                Battle_SetSlotPending(slot);
            }
        }
    }
    return D_801463C2 != 0;
}
