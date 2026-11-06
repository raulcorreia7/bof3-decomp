#include "start_08.h"

MATCH void func_801E55B8(void) {
    s8 count;

    Menu_DrawClutStrip(D_80144953);
    Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    func_801E14A8(0x62 + g_MenuStartTimer * 0x30, 0x4C, D_801ED870, LOBU(g_SaveCardPort), 0);
    count            = g_MenuStartTimer + 1;
    g_MenuStartTimer = count;
    if (count == 4) {
        g_MenuStartStep += 1;
    }
}
