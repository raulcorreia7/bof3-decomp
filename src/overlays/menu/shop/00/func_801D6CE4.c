#include "shop_00.h"

MATCH void func_801D6CE4(u8 slot_index, u8* source_record) {
    g_SaveSlots[slot_index] = *(SaveSlotRow*)(source_record + 0xCA0);
}
