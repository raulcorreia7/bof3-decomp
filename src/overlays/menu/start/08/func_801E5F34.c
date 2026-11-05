#include "start_08.h"

MATCH void func_801E5F34(void) {
    Menu_DrawClutStrip(D_80144953);
    Menu_DrawHeaderBar(0x14, 0x12, 0x118, 0x13, D_80144952);
    SAVE_DrawSlots(0x20, 0x30, 0);
    WinDrawCueText(28, 21, 0xB1);
    UI_SetMode(0);
    g_MenuStartTimer = 0x1E;
    g_MenuStartStep += 1;
}
