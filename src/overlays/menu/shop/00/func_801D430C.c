#include "shop_00.h"

MATCH void func_801D430C(void) {
    u8* counter;

    if (WINDOW_EFFECT_IDLE()) {
        func_801D6E94();
        counter = &g_MenuStep.state;
        *counter += 1;
    } else if (D_8014865C != -1) {
        MENU_DRAW_HEADER();
        WinDrawCueText(MENU_PROMPT_X, MENU_PROMPT_Y, 0xA4);
    }
}
