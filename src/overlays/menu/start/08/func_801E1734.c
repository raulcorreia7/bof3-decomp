#include "start_08.h"

MATCH void func_801E1734(void) {
    Menu_DrawClutStrip(D_80144953);
    Menu_DrawHeaderBar(MENU_HEADER_X, 16, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    func_801E26A8(0x1C, 0x40);
    func_801E2668(0xFF, 0x70, 0x26);
    if (WINDOW_EFFECT_IDLE()) {
        D_80148654 = 0;
        D_80148653 = 0;
        D_80148652 += 1;
    }
}
