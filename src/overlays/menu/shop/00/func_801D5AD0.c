#include "shop_00.h"

MATCH void func_801D5AD0(void) {
    u8  count;
    s8* flag;

    Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    WinDrawCueText(28, 22, 0x91);
    func_801DDFB0(0x62, 0x4C, D_801E60F8, g_SaveCardPort, 1);
    if ((Menu_ToggleOption() & BYTE_MASK) != 0) {
        flag = &D_8014865B;
        if (*flag != 0) {
            SND_PlayCue(EMI_CUE_ID(1, 4));
            count = D_80148652;
            *flag = 0;
            count++;
        } else {
            SND_PlayCue(EMI_CUE_ID(1, 6));
            count = 4;
        }
        D_80148652 = count;
    }
}
