#include "battle_15.h"

MATCH void func_8009AAE8(void) {
    s32 bitIndex;
    s32 record;
    u8  saveBuf;
    u32 selectBit;

    saveBuf   = D_801485A1;
    selectBit = g_CharSlot[D_80144F5D[D_801485C4]];
    if (((Item_GetEquipability(D_8014859C, saveBuf) & 0xFF) >> selectBit) & 1) {
        D_801485C5 = 0;
        bitIndex   = selectBit & 0xFF;
    } else {
        D_801485C5 = 1;
        bitIndex   = selectBit & 0xFF;
    }
    record                             = bitIndex;
    s_BattleEquipment[0]               = g_Characters[record].equip.weapon;
    s_BattleEquipment[1]               = g_Characters[record].equip.shield;
    s_BattleEquipment[2]               = g_Characters[record].equip.helmet;
    s_BattleEquipment[3]               = g_Characters[record].equip.armor;
    s_BattleEquipment[4]               = g_Characters[record].equip.accessories[0];
    s_BattleEquipment[5]               = g_Characters[record].equip.accessories[1];
    s_BattleEquipment[g_BattleItemRow] = saveBuf;
}
