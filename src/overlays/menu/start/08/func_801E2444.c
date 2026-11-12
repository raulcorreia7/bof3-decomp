#include "start_08.h"

MATCH void func_801E2444(void) {
    u8* level;
    u8  value;

    Menu_DrawClutStrip(D_80144953);
    if (g_GameEntryState == 2) {
        Menu_DrawHeaderBar(MENU_HEADER_X, 16, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
        func_801E26A8(0x1C, 0x40);
        func_801E2668(0, 0x70, 0x26);
        UI_SetMode(UI_MODE_FADE_OUT);
        D_8014865F = 0x1E;
        D_80148653 += 1;
        return;
    }
    level = &D_80148654;
    Menu_DrawHeaderBar(MENU_HEADER_X, (0x10 - *level * 0x10) & 0xFFF0, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    func_801E26A8((*level << 6) | 0x1C, 0x40);
    func_801E2668(0, 0x70, 0x26 - *level * 0x10);
    value  = *level + 1;
    *level = value;
    if (value == 5) {
        D_80148651 += 1;
    }
}
