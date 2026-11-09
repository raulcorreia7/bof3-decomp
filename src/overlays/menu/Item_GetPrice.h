/* Read the u16 value of one entry from the four item category tables. */
/* func_801D4F1C (bate), func_801D5EC4 (shisu), func_801DA9C4 (shop), func_801DDEBC (start) */
MATCH u16 Item_GetPrice(ItemCategory category, s32 item_id) {
    s32 category_byte;

    category_byte = category;
    switch (category_byte & BYTE_MASK) {
        case ITEM_CAT_ITEM:
        default:
            return *(u16*)(&D_801C8974 + ((item_id & BYTE_MASK) * 0x12));
        case ITEM_CAT_WEAPON:
            return *(u16*)(&D_801C90F2 + ((item_id & BYTE_MASK) * 0x18));
        case ITEM_CAT_ARMOR:
            return *(u16*)(&D_801C98B8 + ((item_id & BYTE_MASK) * 0x16));
        case ITEM_CAT_ACCESSORY:
            return *(u16*)(&D_801C9E8E + ((item_id & BYTE_MASK) * 0x14));
    }
}
