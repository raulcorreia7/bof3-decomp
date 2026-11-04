#include "engine/slus/slus.h"

/* counts how many of one item the party holds: mode 0 returns its
 * inventory quantity, any other mode counts it among the equipment of the
 * live character records, plus the fishing rod and lures for accessories.
 */
MATCH s32 Party_CountItem(u8 category, u8 item, u8 mode) {
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
    for (i = 0; i < PARTY_RECORD_COUNT; i++) {
        record = &g_Characters[i];
        if (record->unk_07 & 1) {
            switch (category) {
                case ITEM_CAT_ITEM:
                default:
                    break;
                case ITEM_CAT_WEAPON:
                    if (record->weapon == item)
                        count++;
                    break;
                case ITEM_CAT_ARMOR:
                    if (record->shield == item)
                        count++;
                    if (record->helmet == item)
                        count++;
                    if (record->armor == item)
                        count++;
                    break;
                case ITEM_CAT_ACCESSORY:
                    if (record->accessories[0] == item)
                        count++;
                    if (record->accessories[1] == item)
                        count++;
                    break;
            }
        }
    }
    if (category == ITEM_CAT_ACCESSORY) {
        if (MEM(u8, FISHING_ROD) == item)
            count++;
        if (MEM(u8, FISHING_LURE) == item)
            count += MEM(u8, FISHING_LURE_QTY);
    }
    return count;
}
