#include "engine/slus/slus.h"

/* resolves one item record from its category and item: the category
 * selects the item, weapon, armor, accessory or vital-item table, the item the
 * record inside it. Item and out-of-range categories read the item table.
 */
MATCH u8* Item_GetRecord(s32 category, s32 item) {
    switch (category & 0xFF) {
        case ITEM_CAT_ITEM:
        default:
            return (u8*)&g_Items[item & 0xFF];
        case ITEM_CAT_WEAPON:
            return (u8*)&g_Weapons[item & 0xFF];
        case ITEM_CAT_ARMOR:
            return (u8*)&g_Armors[item & 0xFF];
        case ITEM_CAT_ACCESSORY:
            return (u8*)&g_Accessories[item & 0xFF];
        case ITEM_CAT_VITAL:
            return (u8*)&g_VitalItems[item & 0xFF];
    }
}
