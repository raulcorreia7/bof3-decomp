#include "scena10_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH u8 func_801FA5EC(void) {
    u8 i;
    u8 count;

    for (i = 0; i < 8; i += 1) {
        count = Item_Count(ITEM_CATEGORY_ITEM, i + 0x4E, 0);
        if (count != 0) {
            return count;
        }
    }
    return 0;
}

MATCH s32 func_801FA644(void) {
    if (((D_80144908[0] >= 2) && (D_80144908[2] >= 3) && (D_80144908[3] >= 2) && (D_80144908[5] != 0)) && (D_80144908[7] >= 2)) {
        return 1;
    }
    return 0;
}
