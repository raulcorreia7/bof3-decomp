#include "shop_00.h"

MATCH void func_801D3B98(void) {
    u8 count;

    MENU_DRAW_HEADER();
    if (D_8014865C != -1) {
        TEXT_Format(g_UITextFormatBuffer, D_801D0C1C, D_80148699 * 10);
        UI_MessageSetVariable(0, 8, g_UITextFormatBuffer);
        WinDrawCueText(MENU_PROMPT_X, MENU_PROMPT_Y, 0xA1);
        Menu_DrawZennyWindow(MENU_ZENNY_WINDOW_X, MENU_ZENNY_WINDOW_Y, 0, g_Zenny);
    }
    if (g_UIWindowChannel & FRONTEND_FLAG_CONFIRM) {
        count      = D_80148652;
        D_80148654 = 6;
        D_80148652 = count + 1;
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
    }
}
