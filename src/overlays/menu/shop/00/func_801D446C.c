#include "shop_00.h"

MATCH void func_801D446C(void) {
    s16 i;

    Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    if (WINDOW_EFFECT_IDLE()) {
        func_801D68D0(1);
        D_8014865B           = 1;
        D_80148652           = D_80148652 + 1;
        g_InputRepeatButtons = 0;
        g_InputRepeatDelay   = 0;
        if (D_8014865C != -1) {
            Resource_RequestArea(0xD5);
        }
        for (i = 0; i < 4; i++) {
            if (D_801E6100[i] != 0) {
                SsSepReplay(0, i);
            }
        }
    }
}
