#include "start_08.h"

MATCH void func_801E4FFC(void) {
    Menu_DrawClutStrip(D_80144953);
    Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    g_MenuStartTimer      = 2;
    D_801ED7FC            = 2;
    g_MenuStartReturnStep = g_MenuStartStep + 1;
    g_MenuStartStep       = 0xE;
}
