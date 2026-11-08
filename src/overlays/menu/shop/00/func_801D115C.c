#include "shop_00.h"

MATCH void func_801D115C(void) {
    u8  index;
    s32 offset;
    s32 result;

    func_801D3710();
    D_80148654 = 6;
    D_801E6058 = 0;
    D_80148652 += 1;
    for (index = 0; index < D_8018E7CC[0]; index++) {
        offset = index * 2;
        result = Item_GetIcon(*(D_8018E7CC + offset + 1), *(D_8018E7CC + offset + 2)) - 0xA;
        if ((*(D_8018E7CC + offset + 1) != 0) && ((result & BYTE_MASK) >= 2U)) {
            D_801E6058 = 1;
            break;
        }
    }
    func_801D3560(&g_ShopPricePercent);
}
