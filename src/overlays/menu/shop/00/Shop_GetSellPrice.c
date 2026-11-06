#include "shop_00.h"

MATCH u32 Shop_GetSellPrice(s32 item_kind, s32 quantity, s32 discount_flag) {
    s32 kind;
    u32 value;

    kind  = item_kind & 0xFF;
    value = Item_GetPrice(kind, quantity & 0xFF) & 0xFFFF;
    if ((discount_flag & 0xFF) && kind == 0 && ((quantity - 0x2B) & 0xFF) < 0xCU) {
        return value * 0x32;
    }
    return value >> 1;
}
