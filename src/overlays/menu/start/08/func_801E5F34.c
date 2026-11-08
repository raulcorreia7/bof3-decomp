#include "start_08.h"

MATCH void func_801E5F34(void) {
    Menu_DrawClutStrip(D_80144953);
    MENU_DRAW_HEADER();
    SAVE_DrawSlots(SAVE_SLOTS_X, SAVE_SLOTS_Y, 0);
    WinDrawCueText(28, 21, 0xB1);
    UI_SetMode(UI_MODE_FADE_OUT);
    g_MenuStartTimer = 0x1E;
    g_MenuStartStep += 1;
}
