#include "start_08.h"

MATCH void func_801E590C(void) {
    u8 count;

    Menu_DrawClutStrip(D_80144953);
    MENU_DRAW_HEADER();
    WinDrawCueText(28, 21, 0xB9);
    SAVE_DrawSlots(SAVE_SLOTS_X, SAVE_SLOTS_Y, 0);
    if ((Menu_ToggleOption() & BYTE_MASK) != 0) {
        if (D_8014865B != 0) {
            count                 = g_MenuStartStep;
            D_801ED7FC            = 0xA;
            g_MenuStartStep       = 0xE;
            g_MenuStartTimer      = 2;
            g_MenuStartReturnStep = count + 1;
            return;
        }
        g_MenuStartStep--;
    }
}
