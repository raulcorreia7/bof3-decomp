#include "start_08.h"

MATCH void func_801E5674(void) {
    s8 count;

    if (g_MenuStartTimer == 4) {
        SND_PlayCue(EMI_CUE_ID(1, 2));
    }
    Menu_DrawClutStrip(D_80144953);
    Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, D_80144952);
    SAVE_DrawSlots(0x20 - g_MenuStartTimer * 0x50, 0x30, 1);
    count            = g_MenuStartTimer - 1;
    g_MenuStartTimer = count;
    if (count == 0) {
        g_MenuStartStep += 1;
    }
}
