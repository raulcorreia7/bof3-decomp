#include "engine/slus/slus.h"

/* resolves one field record (0x80144968, stride 0xA4) or its battle
 * copy (0x80145F04, stride 0x140) and returns the panel selected by the low two
 * bits of its ability-kind record.
 */
MATCH u8* Char_GetAbilities(u8 character_index, u8 ability_id, u8 mode) {
    Character* record;
    u8         i;

    i = character_index & BYTE_MASK;
    if ((mode & BYTE_MASK) == 0) {
        record = &g_Characters[i];
    } else {
        record = &g_Game.members[i].chr;
    }
    switch (D_801CA719[ability_id & BYTE_MASK].value & 0x3) {
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
