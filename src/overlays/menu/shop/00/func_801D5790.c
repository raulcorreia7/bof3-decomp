#include "shop_00.h"

MATCH void func_801D5790(void) {
    u8 prev;

    g_SaveSlotCount = 3;
    Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, D_80144952);
    WinDrawCueText(28, 22, 0x90);
    SAVE_DrawSlots(0x20, 0x30, 0);
    if (Menu_ToggleOption() & 0xFF) {
        if (D_8014865B != 0) {
            SND_PlayCue(EMI_CUE_ID(1, 4));
            prev       = D_80148652;
            D_801E60EC = 0x16;
            D_80148652 = 0x13;
            D_80148654 = 2;
            D_801E6094 = prev + 1;
            return;
        }
        SND_PlayCue(EMI_CUE_ID(1, 6));
        D_80148652 -= 5;
    }
}
