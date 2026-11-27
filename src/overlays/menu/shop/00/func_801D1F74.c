#include "shop_00.h"

MATCH void func_801D1F74(void) {
    u8*  block;
    s8*  mode;
    u16* pad;
    u16  pad_state;
    s16  count;

    block = Item_GetRecord(g_ShopItemCategory, g_ShopItemId);
    mode  = &D_8014865B;
    pad   = &g_PadStates[0].pressed;
    UI_MessageSetVariable(0, 0xC, block);
    D_80148340                = 0x4A;
    g_UiPanelTasks[21].active = 1;
    g_UiPanelTasks[21].pos.vx = g_UiPanelTasks[0].pos.vx + (1 - *mode) * 32 + 0xDE;
    g_UiPanelTasks[21].pos.vy = g_UiPanelTasks[0].pos.vy + 5;
    if (*pad & (PADLright | PADLleft)) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        *mode = *mode ^ 0x1;
    }
    pad_state = *pad;
    if ((pad_state & g_InputMasks[MENU_INPUT_CONFIRM]) == 0) {
        if ((pad_state & g_InputMasks[MENU_INPUT_CANCEL]) == 0) {
            return;
        }
    } else if (*mode != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        D_80148656 = 0;
        count      = g_MenuStep.state + 1;
        goto store; /* store the computed value */
    }
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
    count = g_MenuStep.state - 3;
store:
    g_MenuStep.state = count;
}
