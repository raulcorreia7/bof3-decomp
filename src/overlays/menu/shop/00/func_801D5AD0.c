#include "shop_00.h"

MATCH void func_801D5AD0(void) {
    u8  count;
    s8* flag;

    MENU_DRAW_HEADER();
    WinDrawCueText(MENU_PROMPT_X, MENU_PROMPT_Y, 0x91);
    SAVE_DrawPortTabs(0x62, 0x4C, D_801E60F8, g_SaveCardPort, 1);
    if ((Menu_ToggleOption() & BYTE_MASK) != 0) {
        flag = &D_8014865B;
        if (*flag != 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
            count = g_MenuStep.state;
            *flag = 0;
            count++;
        } else {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
            count = 4;
        }
        g_MenuStep.state = count;
    }
}
