#include "shop_00.h"

MATCH void func_801D3FD4(void) {
    func_801D6D6C(0x6E, 0x4C);
    MENU_DRAW_HEADER();
    if (D_8014865C != -1) {
        Menu_DrawZennyWindow(MENU_ZENNY_WINDOW_X, MENU_ZENNY_WINDOW_Y, 0, g_Zenny);
    }
    WinDrawCueText(MENU_PROMPT_X, MENU_PROMPT_Y, 0xA2);
    if (g_InputPressed != 0) {
        D_80148652 -= 1;
    }
}
