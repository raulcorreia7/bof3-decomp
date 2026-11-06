#include "engine/slus/slus.h"

/* Previews equipping item_id in a slot: copies the party record, sets the slot,
 * rebuilds the stats on the copy and returns the four stat values with a flag
 * each (3 lower, 2 higher, 0 equal).
 */
/* func_80164D2C */
MATCH void Char_PreviewEquip(u8 character_id, u8 slot, u8 item_id, u8* flags, u16* values) {
    Character  preview;
    u16*       before[4];
    u16*       after[4];
    Character* character;
    u8         i;
    s32        j;

    character = &g_SaveData.characters[character_id];
    before[0] = &character->stats.power;
    before[1] = &character->stats.defense;
    before[2] = &character->stats.intellect;
    before[3] = &character->stats.agility;
    after[0]  = &preview.stats.power;
    after[1]  = &preview.stats.defense;
    after[2]  = &preview.stats.intellect;
    after[3]  = &preview.stats.agility;
    preview   = *character;
    switch (slot) {
        case EQUIP_SLOT_WEAPON:
            preview.equip.weapon = item_id;
            break;
        case EQUIP_SLOT_SHIELD:
            preview.equip.shield = item_id;
            break;
        case EQUIP_SLOT_HELMET:
            preview.equip.helmet = item_id;
            break;
        case EQUIP_SLOT_ARMOR:
            preview.equip.armor = item_id;
            break;
        case EQUIP_SLOT_ACCESSORY_1:
            preview.equip.accessories[0] = item_id;
            break;
        case EQUIP_SLOT_ACCESSORY_2:
            preview.equip.accessories[1] = item_id;
            break;
    }
    Char_RebuildStats(&preview);
    for (i = 0; i < 4; i++) {
        j         = i & BYTE_MASK;
        flags[j]  = 0;
        values[j] = *after[j];
        if (*before[j] < *after[j])
            flags[j] = 3;
        if (*before[j] > *after[j])
            flags[j] = 2;
    }
}
