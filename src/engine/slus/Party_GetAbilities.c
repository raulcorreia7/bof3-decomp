#include "engine/slus/slus.h"

/* resolves the party record a slot kind points at: character records
 *           are selected for mode == 0, formation records otherwise.
 */
MATCH u8* Party_GetAbilities(u32 formation_index, u32 ability_type, u32 mode) {
    Character* record;
    u32        slot;

    if ((mode & BYTE_MASK) == 0) {
        slot   = g_CharSlot[g_PartyFieldOrder[formation_index & BYTE_MASK]];
        record = &g_Characters[slot];
    } else {
        record = &g_BattlePartyBattlers[formation_index & BYTE_MASK].chr;
    }
    switch ((u8)ability_type) {
        default:
            return record->abilities.healing;
        case ABILITY_TYPE_HEAL:
            return record->abilities.healing;
        case ABILITY_TYPE_ASSIST:
            return record->abilities.assist;
        case ABILITY_TYPE_ATTACK:
            return record->abilities.attack;
        case ABILITY_TYPE_SKILL:
            return record->abilities.skill;
    }
}
