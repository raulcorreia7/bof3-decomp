#include "engine/slus/slus.h"

/* Previews equipping item_id in a slot. */
/* func_80164D2C */
MATCH void Char_PreviewEquip(u8 character_id, u8 slot, u8 item_id, u8* flags, u16* values) {
    Character  preview;
    u16*       before[EQUIP_PREVIEW_STAT_COUNT];
    u16*       after[EQUIP_PREVIEW_STAT_COUNT];
    Character* character;
    u8         i;
    s32        j;

    character                       = &g_Characters[character_id];
    before[EQUIP_PREVIEW_POWER]     = &character->stats.power;
    before[EQUIP_PREVIEW_DEFENSE]   = &character->stats.defense;
    before[EQUIP_PREVIEW_INTELLECT] = &character->stats.intellect;
    before[EQUIP_PREVIEW_AGILITY]   = &character->stats.agility;
    after[EQUIP_PREVIEW_POWER]      = &preview.stats.power;
    after[EQUIP_PREVIEW_DEFENSE]    = &preview.stats.defense;
    after[EQUIP_PREVIEW_INTELLECT]  = &preview.stats.intellect;
    after[EQUIP_PREVIEW_AGILITY]    = &preview.stats.agility;
    preview                         = *character;
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
    for (i = 0; i < EQUIP_PREVIEW_STAT_COUNT; i++) {
        j         = i & BYTE_MASK;
        flags[j]  = 0;
        values[j] = *after[j];
        if (*before[j] < *after[j])
            flags[j] = EQUIP_PREVIEW_HIGHER;
        if (*before[j] > *after[j])
            flags[j] = EQUIP_PREVIEW_LOWER;
    }
}
