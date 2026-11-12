#include "engine/slus/slus.h"

/* counts how many of one item the party holds: mode 0 returns its
 * inventory quantity, any other mode counts it among the equipment of the
 * live character records, plus the fishing rod and lures for accessories.
 */
MATCH s32 Item_Count(u8 category, u8 item, u8 mode) {
    u8*        ids;
    u8*        qtys;
    Character* record;
    u8         count;
    u8         i;

    if (mode == 0) {
        ids  = D_801C893C[category];
        qtys = D_801C8950[category];
        for (i = 0; i < INV_SLOTS_PER_CATEGORY; i++) {
            if (item == *ids)
                return *qtys;
            ids++;
            qtys++;
        }
        return 0;
    }
    count = 0;
    for (i = 0; i < CHARACTER_COUNT; i++) {
        record = &g_Characters[i];
        if (record->unk_07 & 0x1) {
            switch (category) {
                case ITEM_CAT_ITEM:
                default:
                    break;
                case ITEM_CAT_WEAPON:
                    if (record->equip.weapon == item)
                        count++;
                    break;
                case ITEM_CAT_ARMOR:
                    if (record->equip.shield == item)
                        count++;
                    if (record->equip.helmet == item)
                        count++;
                    if (record->equip.armor == item)
                        count++;
                    break;
                case ITEM_CAT_ACCESSORY:
                    if (record->equip.accessories[0] == item)
                        count++;
                    if (record->equip.accessories[1] == item)
                        count++;
                    break;
            }
        }
    }
    if (category == ITEM_CAT_ACCESSORY) {
        if (g_FishingRod == item)
            count++;
        if (g_FishingLure == item)
            count += g_FishingLureQty;
    }
    return count;
}
