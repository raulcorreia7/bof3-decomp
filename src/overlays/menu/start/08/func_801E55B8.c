#include "start_08.h"

MATCH void func_801E55B8(void) {
    s8 count;

    Menu_DrawClutStrip(D_80144953);
    Menu_DrawHeaderBar(0x14, 0x12, 0x118, 0x13, D_80144952);
    func_801E14A8(0x62 + g_MenuStartTimer * 0x30, 0x4C, D_801ED870, LOBU(g_SaveCardPort), 0);
    count            = (u8)g_MenuStartTimer + 1;
    g_MenuStartTimer = count;
    if (count == 4) {
        g_MenuStartStep += 1;
    }
}
