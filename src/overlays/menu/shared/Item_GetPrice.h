/* Read the u16 value of one entry from the four item category tables. */
/* func_801D4F1C (bate), func_801D5EC4 (shisu), func_801DA9C4 (shop), func_801DDEBC (start) */
MATCH u16 Item_GetPrice(ItemCategory category, s32 item_id) {
    s32 category_byte;

    category_byte = category;
    switch (category_byte & BYTE_MASK) {
        case ITEM_CATEGORY_ITEM:
        default:
            return g_Items[item_id & BYTE_MASK].price;
        case ITEM_CATEGORY_WEAPON:
            return g_Weapons[item_id & BYTE_MASK].price;
        case ITEM_CATEGORY_ARMOR:
            return g_Armors[item_id & BYTE_MASK].price;
        case ITEM_CATEGORY_ACCESSORY:
            return g_Accessories[item_id & BYTE_MASK].price;
    }
}
