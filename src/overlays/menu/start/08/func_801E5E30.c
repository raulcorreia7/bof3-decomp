#include "start_08.h"

MATCH void func_801E5E30(void) {
    Menu_DrawClutStrip(D_80144953);
    MENU_DRAW_HEADER();
    switch (D_801ED7FC) {
        case 0:
            break;
        case 5:
            func_801E14A8(0x62, 0x4C, D_801ED870, g_SaveCardPort, 0);
            break;
        case 10:
            SAVE_DrawSlots(SAVE_SLOTS_X, SAVE_SLOTS_Y, 0U);
            break;
    }
    UI_DrawText(28, 21, 0, 255U, Message_GetText(D_801ED7FC + 0xA6));
    g_MenuStartTimer -= 1;
    if (g_MenuStartTimer == 0) {
        g_MenuStartStep = g_MenuStartReturnStep;
    }
}
