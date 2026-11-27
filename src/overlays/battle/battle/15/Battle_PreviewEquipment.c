#include "battle_15.h"

/* func_8009AAE8 */
MATCH void Battle_PreviewEquipment(void) {
    s32 bitIndex;
    s32 record;
    u8  saveBuf;
    u32 selectBit;

    saveBuf   = g_UIPanelTasks[17].flags;
    selectBit = g_CharSlot[g_PartyBattleOrder[g_UIPanelTasks[18].unk_0C]];
    if (((Item_GetEquipability(g_UIPanelTasks[17].unk_08, saveBuf) & BYTE_MASK) >> selectBit) & 0x1) {
        g_UIPanelTasks[18].flags = 0;
        bitIndex                 = selectBit & BYTE_MASK;
    } else {
        g_UIPanelTasks[18].flags = 1;
        bitIndex                 = selectBit & BYTE_MASK;
    }
    record                               = bitIndex;
    s_BattleEquipment[0]                 = g_Characters[record].equip.weapon;
    s_BattleEquipment[1]                 = g_Characters[record].equip.shield;
    s_BattleEquipment[2]                 = g_Characters[record].equip.helmet;
    s_BattleEquipment[3]                 = g_Characters[record].equip.armor;
    s_BattleEquipment[4]                 = g_Characters[record].equip.accessories[0];
    s_BattleEquipment[5]                 = g_Characters[record].equip.accessories[1];
    s_BattleEquipment[g_BattleEquipSlot] = saveBuf;
}
