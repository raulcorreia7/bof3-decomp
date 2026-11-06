#include "shop_00.h"

MATCH void func_801D430C(void) {
    u8* counter;

    if (WINDOW_EFFECT_IDLE()) {
        func_801D6E94();
        counter = &D_80148652;
        *counter += 1;
    } else if (D_8014865C != -1) {
        Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
        WinDrawCueText(28, 22, 0xA4);
    }
}
