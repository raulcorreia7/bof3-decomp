#include "engine/slus/slus.h"

/* rescales the ability byte from the 20-byte D_801CA71A rows for the character record character_index selects
 * (0xA4-byte g_Characters rows, or 0x140-byte D_80145F04 rows with mode): flag 0x1A in +0x12/+0x13 halves it (rounded
 * up), flag 0x19 scales it by three rounded up to a quarter, else unchanged.
 */
MATCH u8 Char_GetAbilityCost(u8 character_index, u8 ability_kind, u8 mode) {
    Character* record;
    u16        value;

    if (mode == 0) {
        record = &g_Characters[character_index];
    } else {
        record = (Character*)&D_80145F04[character_index * 0x140];
    }

    value = D_801CA71A[ability_kind * 0x14];

    if ((record->accessories[0] == ACCESSORY_SPIRIT_RING) || (record->accessories[1] == ACCESSORY_SPIRIT_RING)) {
        value = (value + 1) >> 1;
    } else if ((record->accessories[0] == ACCESSORY_SHAMAN_SRING) ||
               (record->accessories[1] == ACCESSORY_SHAMAN_SRING)) {
        value = 3 * value;
        if ((value & 3) != 0) {
            value = (value >> 2) + 1;
        } else {
            value = value >> 2;
        }
    }
    return value;
}
