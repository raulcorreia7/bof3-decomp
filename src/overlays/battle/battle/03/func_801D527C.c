#include "battle_03.h"

/* Ends the round for every sprite slot whose 0x4000 flag is set and whose state reached 3: clears the slot
 * flags, arms the 0x11/6/5 action bytes and opens the round-result overlay. */
MATCH bool func_801D527C(void) {
    s32 count;
    u8  slot;

    count = 0;
    for (slot = 0; slot < BATTLE_PARTY_SLOT_COUNT; slot++) {
        if (func_801D64C4(slot) == 0) {
            if ((g_BattlePartyBattlers[slot].flags_128.value & COMBATANT_FLAG_CHARGING) &&
                (g_BattlePartyBattlers[slot].counter_136 == 3)) {
                count++;
                g_BattlePartyBattlers[slot].mode        = 6;
                g_BattlePartyBattlers[slot].step        = 5;
                g_BattlePartyBattlers[slot].unk_120     = 0x11;
                g_BattlePartyBattlers[slot].counter_136 = 0;
                g_BattlePartyBattlers[slot].unk_04      = 0;
                g_BattlePartyBattlers[slot].unk_03      = 0;
                g_BattlePartyBattlers[slot].flags_128.value &= ~0x4000;
                g_BattlePartyBattlers[slot].hp_change = g_BattlePartyBattlers[slot].stats.current_hp;
                Battle_SetSlotPending(slot);
            }
        }
    }
    for (slot = 3; slot < 11; slot++) {
        if (func_801D64C4(slot) == 0) {
            if ((ENEMY_COMBATANT(slot).flags_104 & COMBATANT_FLAG_CHARGING) &&
                (g_BattlePartyBattlers[slot].counter_136 == 3)) {
                count++;
                ENEMY_COMBATANT(slot).mode            = 6;
                ENEMY_COMBATANT(slot).step            = 5;
                ENEMY_COMBATANT(slot).target_flags_FC = 0x11;
                ENEMY_COMBATANT(slot).unk_112         = 0;
                ENEMY_COMBATANT(slot).unk_04          = 0;
                ENEMY_COMBATANT(slot).unk_03          = 0;
                ENEMY_COMBATANT(slot).flags_104 &= ~COMBATANT_FLAG_CHARGING;
                ENEMY_COMBATANT(slot).damage_F8 = ENEMY_COMBATANT(slot).hp_94;
                Battle_SetSlotPending(slot);
            }
        }
    }
    if (count & BYTE_MASK) {
        func_801D9484();
        func_801DE560(2, 0, 0, 0x2D, Resource_GetText(0x2D));
        return true;
    }
    return false;
}
