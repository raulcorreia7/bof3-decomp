#include "start_08.h"

MATCH void func_801D6FBC(void) {
    s32 record;
    s32 record_index;
    u8  index;
    s32 bit_index;

    index     = g_MenuPanelTasks[14].flags;
    bit_index = g_CharSlot[g_PartyWalkOrder[g_MenuPanelTasks[13].unk_0C]];
    if (((s32)(Item_GetEquipability(g_MenuPanelTasks[14].unk_08, index) & BYTE_MASK) >> bit_index) & 1) {
        g_MenuPanelTasks[13].flags = 0;
        record_index               = bit_index & BYTE_MASK;
    } else {
        g_MenuPanelTasks[13].flags = 1;
        record_index               = bit_index & BYTE_MASK;
    }
    record                                     = record_index;
    D_801ED63C                                 = g_Characters[record].equip.weapon;
    D_801ED63D                                 = g_Characters[record].equip.shield;
    D_801ED63E                                 = g_Characters[record].equip.helmet;
    D_801ED63F                                 = g_Characters[record].equip.armor;
    D_801ED640                                 = g_Characters[record].equip.accessories[0];
    D_801ED641                                 = g_Characters[record].equip.accessories[1];
    (&D_801ED63C)[g_MenuPanelTasks[13].unk_0A] = index;
}
