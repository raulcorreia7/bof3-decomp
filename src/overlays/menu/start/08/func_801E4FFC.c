#include "start_08.h"

MATCH void func_801E4FFC(void) {
    Menu_DrawClutStrip(D_80144953);
    MENU_DRAW_HEADER();
    g_MenuStartTimer      = 2;
    D_801ED7FC            = 2;
    g_MenuStartReturnStep = g_MenuStartStep + 1;
    g_MenuStartStep       = 0xE;
}
