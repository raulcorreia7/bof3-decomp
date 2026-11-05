#include "battle_03.h"

/* resets one local/enemy `0x80` path, zeroes saved values, rebuilds
 * the followup state bytes, and queues the common event when needed.
 */
MATCH u8 func_801D5BC0(void) {
    u8 index;
    u8 count;

    count = 0u;
    for (index = 0u; index < BATTLE_PARTY_SLOT_COUNT; index++) {
        if ((func_801D64C4(index) == 0u) && (HAS_STATUS(g_BattlePartyBattlers[index], STATUS_POISONED))) {
            g_BattlePartyBattlers[index].ap_change = 0u;
            g_BattlePartyBattlers[index].hp_change = 0u;
            func_801DCEF8(index);
            count += 1u;
            g_BattlePartyBattlers[index].mode    = 6u;
            g_BattlePartyBattlers[index].step    = 5u;
            g_BattlePartyBattlers[index].unk_04  = 0u;
            g_BattlePartyBattlers[index].unk_03  = 0u;
            g_BattlePartyBattlers[index].unk_120 = 0x11u;
            Battle_SetSlotPending(index);
        }
    }

    for (index = 3u; index < 11u; index++) {
        if ((func_801D64C4(index) == 0u) && ((ENEMY_COMBATANT(index).status_82 & STATUS_POISONED) != 0u)) {
            ENEMY_COMBATANT(index).unk_FA    = 0u;
            ENEMY_COMBATANT(index).damage_F8 = 0u;
            func_801DCEF8(index);
            count += 1u;
            ENEMY_COMBATANT(index).mode            = 6u;
            ENEMY_COMBATANT(index).step            = 5u;
            ENEMY_COMBATANT(index).unk_04          = 0u;
            ENEMY_COMBATANT(index).unk_03          = 0u;
            ENEMY_COMBATANT(index).target_flags_FC = 0x11u;
            Battle_SetSlotPending(index);
        }
    }

    if (count != 0u) {
        func_801D9484();
        func_801DE560(2u, 0u, 0u, 0x2Du, Resource_GetText(0x18u));
        return true;
    }

    return false;
}
