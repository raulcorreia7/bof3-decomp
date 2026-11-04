#include "shop_00.h"

MATCH u32 Shop_GetSellPrice(s32 item_kind, s32 quantity, s32 discount_flag) {
    s32 kind;
    u32 value;

    kind  = item_kind & BYTE_MASK;
    value = Item_GetPrice(kind, quantity & BYTE_MASK) & HALF_MASK;
    if ((discount_flag & BYTE_MASK) && kind == 0 && (u32)((quantity - 0x2B) & BYTE_MASK) < 0xCU) {
        return value * 0x32;
    }
    return value >> 1;
}
