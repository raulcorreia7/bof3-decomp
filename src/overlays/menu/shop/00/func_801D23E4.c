#include "shop_00.h"

MATCH void func_801D23E4(void) {
    s32 selection;
    s32 input;
    s32 paged;
    u8  index;
    u16 row_y;
    u8* cursor;
    u8* step;

    selection                 = Item_GetIcon(g_ShopItemCategory, g_ShopItemId);
    index                     = selection;
    g_UiPanelTasks[21].active = 1;
    D_80148628                = g_UiPanelTasks[6].pos.vx + 6;
    paged                     = D_801E6054 - 1;
    row_y                     = (index + paged) * 0xD + 0x1A;
    D_8014862A                = g_UiPanelTasks[6].pos.vy + row_y;
    input                     = INPUT_REPEATED(g_PadStates[0].pressed, (PADLup | PADLdown));
    if (index - 1 == 4) {
        D_80148340 = 0x4C;
        if (input & (PADLup | PADLdown)) {
            D_801E6054 ^= 1;
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        }
    } else {
        UI_MessageSetVariable(0, 0xC, Item_GetRecord(g_ShopItemCategory, g_ShopItemId));
        D_80148340 = 0x3A;
    }
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
        cursor = &D_80148656;
        Shop_Equip(g_CharSlot[g_PartyFieldOrder[(s8)*cursor]], (selection + (D_801E6054 + 0xFF)) & BYTE_MASK, g_ShopItemId);
        Char_RebuildStats(&g_Characters[g_CharSlot[g_PartyFieldOrder[(s8)*cursor]]]);
        D_80148652 += 1;
    } else if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        for (index = 0; index < Party_CountOrder(PARTY_ORDER_FIELD); index++) {
            if (index == (s8)D_80148656) {
                g_UiPanelTasks[index + 3].state = 4;
            } else {
                g_UiPanelTasks[index + 3].state = 2;
            }
        }
        g_UiPanelTasks[6].state = 1;
        step                    = &D_80148652;
        (*step)--;
    }
}
