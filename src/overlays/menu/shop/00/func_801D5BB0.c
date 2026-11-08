#include "shop_00.h"

MATCH void func_801D5BB0(void) {
    u8 prev;

    MENU_DRAW_HEADER();
    WinDrawCueText(MENU_PROMPT_X, MENU_PROMPT_Y, 0x92);
    func_801DDFB0(0x62, 0x4C, D_801E60F8, g_SaveCardPort, 1);
    if (Menu_ToggleOption() & BYTE_MASK) {
        if (D_8014865B != 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
            prev       = D_80148652;
            D_801E60EC = SAVE_WAIT_FORMAT;
            D_80148652 = 0x13;
            D_80148654 = 2;
            D_801E6094 = prev + 1;
        } else {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
            D_80148652 = 4;
        }
    }
}
