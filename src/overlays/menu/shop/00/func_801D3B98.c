#include "shop_00.h"

MATCH void func_801D3B98(void) {
    u8 count;

    MENU_DRAW_HEADER();
    if (D_8014865C != -1) {
        TEXT_Format(g_UiFormatBuffer, D_801D0C1C, D_80148699 * 10);
        Message_SetVariable(0, 8, g_UiFormatBuffer);
        WinDrawCueText(28, 22, 0xA1);
        Menu_DrawZennyWindow(0x62, 0x28, 0, g_Zenny);
    }
    if (g_UiWindowChannel & FRONTEND_FLAG_CONFIRM) {
        count      = D_80148652;
        D_80148654 = 6;
        D_80148652 = count + 1;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
    }
}
