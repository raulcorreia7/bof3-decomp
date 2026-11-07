#include "start_08.h"

MATCH s32 func_801D70EC(void) {
    s32 record;

    record                                 = g_CharSlot[g_PartyFieldOrder[g_MenuPanelTasks[13].unk_0C]];
    g_EquipPreview[EQUIP_SLOT_WEAPON]      = g_Characters[record].equip.weapon;
    g_EquipPreview[EQUIP_SLOT_SHIELD]      = g_Characters[record].equip.shield;
    g_EquipPreview[EQUIP_SLOT_HELMET]      = g_Characters[record].equip.helmet;
    g_EquipPreview[EQUIP_SLOT_ARMOR]       = g_Characters[record].equip.armor;
    g_EquipPreview[EQUIP_SLOT_ACCESSORY_1] = g_Characters[record].equip.accessories[0];
    g_EquipPreview[EQUIP_SLOT_ACCESSORY_2] = g_Characters[record].equip.accessories[1];
    if (g_EquipPreview[D_8014850E] != 0) {
        g_EquipPreview[D_8014850E] = 0;
        g_MenuPanelTasks[13].flags = 0;
        return 1;
    }
    g_MenuPanelTasks[13].flags = 1;
    return 0;
}
