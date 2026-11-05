#include "start_08.h"

MATCH void func_801E4F50(void) {
    Menu_DrawClutStrip(D_80144953);
    Menu_DrawHeaderBar(0x14, (g_MenuStartTimer * 20 + 0x12) & 0xFFFE, 0x118, 0x13, D_80144952);
    if (g_MenuStartTimer > 0) {
        g_MenuStartTimer--;
    }
    if (WINDOW_EFFECT_IDLE()) {
        g_MenuStartStep++;
    }
}
