#include "engine/slus/slus.h"

/* resolves one field record (0x80144968, stride 0xA4) or its battle
 * copy (0x80145F04, stride 0x140) and returns the panel selected by the low two
 * bits of its ability-kind record.
 */
MATCH u8* Char_GetAbilities(u8 character_index, u8 ability_kind, u8 mode) {
    Character* record;
    u8         i;

    i = character_index & BYTE_MASK;
    if ((mode & BYTE_MASK) == 0) {
        record = &g_Characters[i];
    } else {
        record = (Character*)(D_80145F04 + i * 0x140);
    }
    switch (D_801CA719[ability_kind & BYTE_MASK].value & 0x3) {
        default:
            return record->healing_abilities;
        case 0:
            return record->healing_abilities;
        case 1:
            return record->assist_abilities;
        case 2:
            return record->attack_abilities;
        case 3:
            return record->skill_abilities;
    }
}
