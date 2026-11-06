#include "start_08.h"

/* The 0xA4-byte rows of g_Characters are Character records
 * (include/game/character.h); the 0x140-byte rows of D_80145F04 carry the same
 * AP halfword at +0x16. Both are read through one byte pointer, as in the
 * matched sibling func_801E8580. */

MATCH s32 func_801E7D20(s32 character_index, s32 target_index, s32 ability_id, s32 use_battle_record) {
    Character* record;
    s32        character;
    u8         ability;
    s32        cost;

    if (use_battle_record & 0xFF) {
        record = (Character*)&D_80145F04[(character_index & 0xFF) * BATTLE_PARTY_STRIDE];
    } else {
        record = &g_Characters[character_index & 0xFF];
    }

    ability = ability_id;
    cost    = Char_GetAbilityCost(character_index & 0xFF, ability, 0) & 0xFF;
    if (record->ap < (u32)cost) {
        return 0;
    }

    if ((u32)((ability_id - 0x46) & 0xFF) < 6) {
        cost = ability_id - 0x45;
    } else if ((u32)((ability_id + 0x52) & 0xFF) < 6) {
        cost = ability_id + 0x53;
    } else if (ability == ABILITY_REMEDY || ability == 0xD7) {
        cost = 8;
    } else if (ability == 0x50) {
        cost = 7;
    } else {
        cost = (ability == ABILITY_CURE) ? 9 : 0;
    }

    character = character_index & 0xFF;
    ability   = D_801ED224[cost & 0xFF](character, target_index & 0xFF, use_battle_record & 0xFF);
    if ((ability & 0xFF) == 1 || (ability & 0xFF) == 5) {
        record->ap -= Char_GetAbilityCost(character, ability_id & 0xFF, 0) & 0xFF;
    }

    return ability & 0xFF;
}
