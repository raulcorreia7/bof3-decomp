#include "shop_00.h"

MATCH void func_801D23E4(void) {
    s32 selection;
    s32 input;
    s32 paged;
    u8  index;
    u16 row_y;
    u8* cursor;
    u8* step;

    selection  = Item_GetKind(g_ShopItemCategory, g_ShopItemId);
    index      = selection;
    D_80148624 = 1;
    D_80148628 = D_8014840C + 6;
    paged      = D_801E6054 - 1;
    row_y      = (index + paged) * 0xD + 0x1A;
    D_8014862A = D_8014840E + row_y;
    input      = INPUT_REPEATED(g_InputPressed, (PADLup | PADLdown));
    if (index - 1 == 4) {
        D_80148340 = 0x4C;
        if (input & (PADLup | PADLdown)) {
            D_801E6054 ^= 1;
            SND_PlayCue(EMI_CUE_ID(1, 0));
        }
    } else {
        TEXT_SetVariable(0, 0xC, Item_GetRecord(g_ShopItemCategory, g_ShopItemId));
        D_80148340 = 0x3A;
    }
    if (g_InputPressed & D_80145AC2) {
        SND_PlayCue(EMI_CUE_ID(1, 4));
        cursor = &D_80148656;
        Shop_Equip(g_CharSlot[D_80144F5A[(s8)*cursor]], (selection + (D_801E6054 + 0xFF)) & BYTE_MASK, g_ShopItemId);
        Char_RebuildStats(&g_SaveData.characters[g_CharSlot[D_80144F5A[(s8)*cursor]]]);
        D_80148652 += 1;
    } else if (g_InputPressed & D_80145AC4) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        for (index = 0; index < Party_CountOrder(0); index++) {
            if (index == (s8)D_80148656) {
                g_MenuPanelTasks[index + 3].state = 4;
            } else {
                g_MenuPanelTasks[index + 3].state = 2;
            }
        }
        D_8014840B = 1;
        step       = &D_80148652;
        (*step)--;
    }
}
