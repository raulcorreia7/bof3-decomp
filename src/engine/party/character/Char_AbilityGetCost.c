#include "engine/slus/slus.h"

/* rescales the ability byte from the g_Abilities rows for the character record character_index selects
 * (0xA4-byte g_Characters rows, or 0x140-byte D_80145F04 rows with mode): flag 0x1A in +0x12/+0x13 halves it (rounded
 * up), flag 0x19 scales it by three rounded up to a quarter, else unchanged.
 */
MATCH u8 Char_AbilityGetCost(u8 character_index, u8 ability_type, u8 mode) {
    Character* record;
    u16        value;

    if (mode == 0) {
        record = &g_Characters[character_index];
    } else {
        record = &g_Game.members[character_index].chr;
    }

    /* kept: the volatile table read changes the retail register schedule. */
    value = ((Ability*)g_Abilities)[ability_type].cost;

    if ((record->equip.accessories[0] == ACCESSORY_SPIRIT_RING) || (record->equip.accessories[1] == ACCESSORY_SPIRIT_RING)) {
        value = (value + 1) >> 1;
    } else if ((record->equip.accessories[0] == ACCESSORY_SHAMANS_RING) || (record->equip.accessories[1] == ACCESSORY_SHAMANS_RING)) {
        value = 3 * value;
        if ((value & 0x3) != 0) {
            value = (value >> 2) + 1;
        } else {
            value = value >> 2;
        }
    }
    return value;
}
