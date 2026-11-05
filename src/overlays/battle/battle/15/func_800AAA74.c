#include "battle_15.h"

/* Absolute-address globals referenced only here. Left undefined in this
 * translation unit so address math lowers to %hi/%lo relocation pairs like
 * the original object code; definitions resolve via the module symbol list. */

/* Party formation shared with the camera task; 1=attack, 2=defense, 3=chain,
 * 4=magic. Read once per selection-phase tick (see func_800A2880.c). */

/* applies the formation's stat changes to the party during the selection phase.
 * Char_AddStat moves a 0..999 stat by a delta; by formation (1=attack, 2=defense, 3=chain, 4=magic) the
 * base power, defence, reprisal chance, agility or intellect of the party rows is eased.
 */
MATCH void func_800AAA74(void) {
    u16 value;
    u16 copy;
    u8  slot;

    switch (g_PartyFormation) {
        case PARTY_FORMATION_ATTACK:
            Char_AddStat(&g_BattlePartyBattlers[0].stats.base_stats.power,
                         (s32)((u32)g_BattlePartyBattlers[0].stats.base_stats.power >> 1u));
            Char_AddStat(&g_BattlePartyBattlers[0].stats.base_stats.defense,
                         -((s32)((u32)g_BattlePartyBattlers[0].stats.base_stats.defense >> 2u)));
            Char_AddPercent(&g_BattlePartyBattlers[0].stats.base_stats.reprisal_chance,
                            g_BattlePartyBattlers[0].stats.base_stats.reprisal_chance);
            return;
        case PARTY_FORMATION_DEFENSE:
            if (g_BattlePartyCount != 0u) {
                slot = 0u;
                do {
                    if (Battle_SlotIsBlocked(slot) == 0u) {
                        Char_AddStat(&g_BattlePartyBattlers[slot].stats.base_stats.agility,
                                     -((s32)((u32)g_BattlePartyBattlers[slot].stats.base_stats.agility >> 2u)));
                    }
                    slot += 1u;
                } while (slot < g_BattlePartyCount);
            }
            return;
        case PARTY_FORMATION_CHAIN:
            if (g_BattlePartyCount != 0u) {
                slot = 0u;
                do {
                    if (Battle_SlotIsBlocked(slot) == 0u) {
                        value = g_BattlePartyBattlers[slot].stats.base_stats.defense;
                        copy  = g_BattlePartyBattlers[0].stats.base_stats.agility;
                        /* plain store: this driver owns the stat; only readers on the
                         * camera side need volatile ordering */
                        g_BattlePartyBattlers[slot].stats.base_stats.agility = copy;
                        Char_AddStat(&g_BattlePartyBattlers[slot].stats.base_stats.defense, -((s32)((u32)value >> 1u)));
                    }
                    slot += 1u;
                } while (slot < g_BattlePartyCount);
            }
            break;
        case PARTY_FORMATION_MAGIC:
            Char_AddStat(&g_BattlePartyBattlers[2].stats.base_stats.intellect,
                         (s32)((u32)g_BattlePartyBattlers[2].stats.base_stats.intellect >> 1u));
            Char_AddStat(&g_BattlePartyBattlers[0].stats.base_stats.intellect,
                         -((s32)((u32)g_BattlePartyBattlers[0].stats.base_stats.intellect >> 2u)));
            Char_AddStat(&g_BattlePartyBattlers[1].stats.base_stats.intellect,
                         -((s32)((u32)g_BattlePartyBattlers[1].stats.base_stats.intellect >> 2u)));
            break;
    }
}

/* Local weak bindings (same mechanism as symbols.c) so the diff link step
 * resolves these addresses; they do not affect compilation. */
