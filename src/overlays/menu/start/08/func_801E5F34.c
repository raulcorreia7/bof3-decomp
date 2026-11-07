#include "start_08.h"

MATCH void func_801E5F34(void) {
    Menu_DrawClutStrip(D_80144953);
    Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    SAVE_DrawSlots(0x20, 0x30, 0);
    WinDrawCueText(28, 21, 0xB1);
    UI_SetMode(UI_MODE_FADE_OUT);
    g_MenuStartTimer = 0x1E;
    g_MenuStartStep += 1;
}
