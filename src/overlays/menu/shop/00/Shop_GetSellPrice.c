#include "shop_00.h"

MATCH u32 Shop_GetSellPrice(ItemCategory category, s32 item_id, s32 antique_shop) {
    s32 category_byte;
    u32 value;

    category_byte = category & BYTE_MASK;
    value         = Item_GetPrice(category_byte, item_id & BYTE_MASK) & HALF_MASK;
    if ((antique_shop & BYTE_MASK) && category_byte == ITEM_CAT_ITEM && ((item_id - SHOP_ANTIQUE_FIRST) & BYTE_MASK) < SHOP_ANTIQUE_COUNT) {
        return value * SHOP_ANTIQUE_PRICE_MULTIPLIER;
    }
    return value >> 1;
}
