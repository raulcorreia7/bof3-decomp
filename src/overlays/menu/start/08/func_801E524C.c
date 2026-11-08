#include "start_08.h"

MATCH void func_801E524C(void) {
    s8 count;

    if (g_MenuStartTimer == 4) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
    }
    Menu_DrawClutStrip(D_80144953);
    MENU_DRAW_HEADER();
    func_801E14A8(0x62 - g_MenuStartTimer * 0x30, 0x4C, D_801ED870, g_SaveCardPort, 0);
    count            = g_MenuStartTimer - 1;
    g_MenuStartTimer = count;
    if (count == 0) {
        g_MenuStartStep += 1;
    }
}
