#include "shop_00.h"

MATCH void func_801D3FD4(void) {
    func_801D6D6C(0x6E, 0x4C);
    MENU_DRAW_HEADER();
    if (D_8014865C != -1) {
        Menu_DrawZennyWindow(0x62, 0x28, 0, g_Zenny);
    }
    WinDrawCueText(28, 22, 0xA2);
    if (g_InputPressed != 0) {
        D_80148652 -= 1;
    }
}
