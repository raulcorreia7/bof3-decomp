#include "start_08.h"

MATCH void func_801E5BCC(void) {
    Menu_DrawClutStrip(D_80144953);
    Menu_DrawHeaderBar(0x14, 0x12, 0x118, 0x13, D_80144952);
    SAVE_DrawSlots((g_MenuStartTimer * 0x50) + 0x20, 0x30, 0);
    g_MenuStartTimer += 1;
    if (g_MenuStartTimer == 4) {
        g_MenuStartStep = 2;
    }
}
