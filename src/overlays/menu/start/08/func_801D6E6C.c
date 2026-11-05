#include "start_08.h"

MATCH void func_801D6E6C(void) {
    u8*        ptrs[6];
    Character* record;
    s32        i;
    u8         want;

    i       = 0;
    record  = &g_Characters[g_CharSlot[D_80144F5A[D_80148510]]];
    ptrs[0] = &record->equipment.weapon;
    ptrs[1] = &record->equipment.shield;
    ptrs[2] = &record->equipment.helmet;
    ptrs[3] = &record->equipment.armor;
    ptrs[4] = &record->equipment.accessories[0];
    ptrs[5] = &record->equipment.accessories[1];
    do {
        want = (&D_801ED63C)[i & BYTE_MASK];
        if (want != 0) {
            if (want != *ptrs[i & BYTE_MASK]) {
                Item_Remove(s_EquipSlotCategories[i & BYTE_MASK], want, 1, 0);
                Item_Add(s_EquipSlotCategories[i & BYTE_MASK], *ptrs[i & BYTE_MASK], 1, 0);
                *ptrs[i & BYTE_MASK] = (&D_801ED63C)[i & BYTE_MASK];
            }
        }
        i++;
    } while ((u8)i < 6);
    Char_RebuildStats(record);
}
