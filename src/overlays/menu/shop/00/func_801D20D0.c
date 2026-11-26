#include "shop_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801D20D0(void) {
    s32 buttons;
    u8  count;
    u8  old;
    u8* cursor;
    s8  i;
    s32 idx;

    UI_MessageSetVariable(0, 0xC, Item_GetRecord(g_ShopItemCategory, g_ShopItemId));
    g_UiPanelTasks[0].u.addr.unk_10 = 0x4B;
    D_80148624                      = 0;
    /* FAKE: block boundary keeps the panel-task stores base-relative off one la. */
    FAKE_ORDER_FENCE();
    cursor                    = &D_80148656;
    idx                       = (s8)*cursor + 3;
    g_UiPanelTasks[20].active = 1;
    D_80148604                = g_UiPanelTasks[idx].pos.vx;
    /* FAKE: block boundary keeps each copy beside its own load. */
    FAKE_ORDER_FENCE();
    D_80148606 = g_UiPanelTasks[idx].pos.vy;
    count      = Party_CountOrder(PARTY_ORDER_FIELD);
    buttons    = INPUT_REPEATED(g_PadStates[0].pressed, (PADLup | PADLdown));
    old        = *cursor;
    if (buttons & PADLup) {
        if ((s8)(*cursor = old - 1) < 0) {
            *cursor = count - 1;
        }
    } else if (buttons & PADLdown) {
        if ((s8)(*cursor = old + 1) > (s8)count - 1) {
            *cursor = 0;
        }
    }
    cursor = &D_80148656;
    if ((s8)old != (s8)*cursor) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
    }
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if ((Item_GetEquipability(g_ShopItemCategory, g_ShopItemId) >> g_CharSlot[g_PartyFieldOrder[(s8)*cursor]]) & 1) {
            for (i = 0; i < (u8)Party_CountOrder(PARTY_ORDER_FIELD); i++) {
                if (i == (s8)D_80148656) {
                    g_UiPanelTasks[i + 3].state = 3;
                } else {
                    g_UiPanelTasks[i + 3].state = 1;
                }
            }
            D_80148408         = 1;
            D_80148409         = 7;
            D_8014840A         = 6;
            D_8014840B         = 2;
            *(s16*)&D_8014840C = -0x96;
            D_8014840E         = 0x74;
            D_80148412         = D_80148656;
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
            D_80148600 = 0;
            D_801E6054 = 0;
            D_80148654 = 5;
            D_80148652 += 1;
        } else {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
        }
    } else if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        D_80148600 = 0;
        D_80148652 -= 4;
    }
}
#else
INCLUDE_ASM(func_801D20D0);
#endif
