#include "start_08.h"

MATCH void func_801D6FBC(void) {
    s32 record;
    s32 record_index;
    u8  index;
    s32 bit_index;

    index     = g_MenuPanelTasks[14].flags;
    bit_index = g_CharSlot[g_PartyFieldOrder[g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0C]];
    if (((s32)(Item_GetEquipability(g_MenuPanelTasks[14].unk_08, index) & BYTE_MASK) >> bit_index) & 0x1) {
        g_MenuPanelTasks[MENU_START_PANEL_ITEMS].flags = 0;
        record_index                                   = bit_index & BYTE_MASK;
    } else {
        g_MenuPanelTasks[MENU_START_PANEL_ITEMS].flags = 1;
        record_index                                   = bit_index & BYTE_MASK;
    }
    record                                                          = record_index;
    g_EquipPreview[EQUIP_SLOT_WEAPON]                               = g_Characters[record].equip.weapon;
    g_EquipPreview[EQUIP_SLOT_SHIELD]                               = g_Characters[record].equip.shield;
    g_EquipPreview[EQUIP_SLOT_HELMET]                               = g_Characters[record].equip.helmet;
    g_EquipPreview[EQUIP_SLOT_ARMOR]                                = g_Characters[record].equip.armor;
    g_EquipPreview[EQUIP_SLOT_ACCESSORY_1]                          = g_Characters[record].equip.accessories[0];
    g_EquipPreview[EQUIP_SLOT_ACCESSORY_2]                          = g_Characters[record].equip.accessories[1];
    g_EquipPreview[g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0A] = index;
}
