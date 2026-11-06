#include "start_08.h"

MATCH void func_801D6E6C(void) {
    u8*        ptrs[6];
    Character* record;
    s32        i;
    u8         want;

    i       = 0;
    record  = &g_Characters[g_CharSlot[D_80144F5A[g_MenuPanelTasks[13].unk_0C]]];
    ptrs[0] = &record->equip.weapon;
    ptrs[1] = &record->equip.shield;
    ptrs[2] = &record->equip.helmet;
    ptrs[3] = &record->equip.armor;
    ptrs[4] = &record->equip.accessories[0];
    ptrs[5] = &record->equip.accessories[1];
    do {
        want = (&D_801ED63C)[i & 0xFF];
        if (want != 0) {
            if (want != *ptrs[i & 0xFF]) {
                Item_Remove(s_EquipSlotCategories[i & 0xFF], want, 1, 0);
                Item_Add(s_EquipSlotCategories[i & 0xFF], *ptrs[i & 0xFF], 1, 0);
                *ptrs[i & 0xFF] = (&D_801ED63C)[i & 0xFF];
            }
        }
        i++;
    } while ((u8)i < 6);
    Char_RebuildStats(record);
}
