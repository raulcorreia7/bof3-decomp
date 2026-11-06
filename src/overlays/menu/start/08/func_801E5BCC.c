#include "start_08.h"

MATCH void func_801E5BCC(void) {
    Menu_DrawClutStrip(D_80144953);
    Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    SAVE_DrawSlots((g_MenuStartTimer * 0x50) + 0x20, 0x30, 0);
    g_MenuStartTimer += 1;
    if (g_MenuStartTimer == 4) {
        g_MenuStartStep = 2;
    }
}
