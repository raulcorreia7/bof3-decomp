#include "engine/slus/slus.h"

/* counts how many of one item_id the party holds: mode 0 returns its
 * inventory quantity, any other mode counts it among the equipment of the
 * live character records, plus the fishing rod and lures for accessories.
 */
MATCH s32 Item_Count(u8 category, u8 item_id, u8 mode) {
    u8*        ids;
    u8*        qtys;
    Character* record;
    u8         count;
    u8         i;

    if (mode == 0) {
        ids  = D_801C893C[category];
        qtys = D_801C8950[category];
        for (i = 0; i < INV_SLOTS_PER_CATEGORY; i++) {
            if (item_id == *ids)
                return *qtys;
            ids++;
            qtys++;
        }
        return 0;
    }
    count = 0;
    for (i = 0; i < CHAR_INDEX_COUNT; i++) {
        record = &g_Characters[i];
        if (record->party_flags & 0x1) {
            switch (category) {
                case ITEM_CATEGORY_ITEM:
                default:
                    break;
                case ITEM_CATEGORY_WEAPON:
                    if (record->equip.weapon == item_id)
                        count++;
                    break;
                case ITEM_CATEGORY_ARMOR:
                    if (record->equip.shield == item_id)
                        count++;
                    if (record->equip.helmet == item_id)
                        count++;
                    if (record->equip.armor == item_id)
                        count++;
                    break;
                case ITEM_CATEGORY_ACCESSORY:
                    if (record->equip.accessories[0] == item_id)
                        count++;
                    if (record->equip.accessories[1] == item_id)
                        count++;
                    break;
            }
        }
    }
    if (category == ITEM_CATEGORY_ACCESSORY) {
        if (g_FishingEquipment.rod_id == item_id)
            count++;
        if (g_FishingEquipment.lure_id == item_id)
            count += g_FishingEquipment.lure_count;
    }
    return count;
}
