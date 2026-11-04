#include "area039_13.h"

MATCH void func_801F2F0C(void) {
    s32 index;
    u8* item;

    item  = g_VitalItemIds;
    index = 0;
    do {
        if (*item == 0xE) {
            *item = 4;
            return;
        }
        index += 1;
        item += 1;
    } while ((u32)(index & BYTE_MASK) < 0x20U);
    Party_AddVitalItem(4);
}
