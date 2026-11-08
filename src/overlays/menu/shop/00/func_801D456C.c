#include "shop_00.h"

MATCH void func_801D456C(void) {
    s32 confirm;

    MENU_DRAW_HEADER();
    if (D_8014865C != -1) {
        confirm = g_UiWindowChannel & FRONTEND_FLAG_CONFIRM;
    } else {
        WinDrawCueText(MENU_PROMPT_X, MENU_PROMPT_Y, 0x1D);
        confirm = Menu_ToggleOption() & BYTE_MASK;
    }
    if (confirm != 0) {
        D_80148652 += 1;
    }
}
