#include "start_08.h"

MATCH void func_801D9B2C(void) {
    u8* timer;
    u8  i;

    Menu_DrawClutStrip(g_WindowClut);
    timer = &D_80148654;
    if (TIMER_EXPIRED(*timer)) {
        i = 0;
        while (i < Party_CountOrder(PARTY_ORDER_FIELD)) {
            /* FAKE: retail reads g_UIPanelTasks[0].unk_0B as u8[]. */
            ((u8*)&g_UIPanelTasks[0].unk_0B)[((i + 4) * 9) << 2] = 1;
            i++;
        }
        timer = &g_MenuStep.state;
        (*timer)++;
    }
}
