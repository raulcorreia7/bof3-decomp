#include "start_08.h"

extern s8 D_801ED7FC;            /* local: s8 read; a sibling copy is u8 */
extern s8 g_MenuStartReturnStep; /* local: s8 read; a sibling copy is u8 */

MATCH void func_801E590C(void) {
    u8 count;

    Menu_DrawClutStrip(D_80144953);
    Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, D_80144952);
    WinDrawCueText(28, 21, 0xB9);
    SAVE_DrawSlots(0x20, 0x30, 0);
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
