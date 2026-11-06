#include "start_08.h"

MATCH s32 func_801D70EC(void) {
    s32 record;

    record     = g_CharSlot[D_80144F5A[g_MenuPanelTasks[13].unk_0C]];
    D_801ED63C = g_SaveData.characters[record].equip.weapon;
    D_801ED63D = g_SaveData.characters[record].equip.shield;
    D_801ED63E = g_SaveData.characters[record].equip.helmet;
    D_801ED63F = g_SaveData.characters[record].equip.armor;
    D_801ED640 = g_SaveData.characters[record].equip.accessories[0];
    D_801ED641 = g_SaveData.characters[record].equip.accessories[1];
    if ((&D_801ED63C)[D_8014850E] != 0) {
        (&D_801ED63C)[D_8014850E]  = 0;
        g_MenuPanelTasks[13].flags = 0;
        return 1;
    }
    g_MenuPanelTasks[13].flags = 1;
    return 0;
}
