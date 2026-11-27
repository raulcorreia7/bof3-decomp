#include "start_08.h"

MATCH void func_801DA8E0(void) {
    u8* timer;
    u8  i;

    Menu_DrawClutStrip(g_WindowClut);
    timer = &D_80148654;
    if (TIMER_EXPIRED(*timer)) {
        i = 0;
        while (i < Party_CountOrder(PARTY_ORDER_FIELD)) {
            g_UIPanelTasks[i + 4].unk_0C = 0;
            i++;
        }
        timer = &g_MenuStep.sub_step;
        *timer -= 2;
    }
}
