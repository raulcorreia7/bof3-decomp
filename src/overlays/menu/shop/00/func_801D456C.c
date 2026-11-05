#include "shop_00.h"

MATCH void func_801D456C(void) {
    s32 confirm;

    Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, D_80144952);
    if (D_8014865C != -1) {
        confirm = g_UiWindowChannel & FRONTEND_FLAG_CONFIRM;
    } else {
        WinDrawCueText(28, 22, 0x1D);
        confirm = Menu_ToggleOption() & BYTE_MASK;
    }
    if (confirm != 0) {
        D_80148652 += 1;
    }
}
