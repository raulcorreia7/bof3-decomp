#include "start_08.h"

MATCH void func_801E5BCC(void) {
    Menu_DrawClutStrip(g_WindowClut);
    MENU_DRAW_HEADER();
    SAVE_DrawSlots((g_MenuStartTimer * 0x50) + SAVE_SLOTS_X, SAVE_SLOTS_Y, 0);
    g_MenuStartTimer += 1;
    if (g_MenuStartTimer == 4) {
        g_MenuCampStep = 2;
    }
}
