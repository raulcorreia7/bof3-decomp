#include "start_08.h"

MATCH void func_801E4F50(void) {
    Menu_DrawClutStrip(D_80144953);
    Menu_DrawHeaderBar(MENU_HEADER_X, (g_MenuStartTimer * 20 + 0x12) & 0xFFFE, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT,
                       g_WindowStyle);
    if (g_MenuStartTimer > 0) {
        g_MenuStartTimer--;
    }
    if (WINDOW_EFFECT_IDLE()) {
        g_MenuStartStep++;
    }
}
