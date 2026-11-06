#include "start_08.h"

MATCH void func_801D9B2C(void) {
    u8* timer;
    u8  i;

    Menu_DrawClutStrip(D_80144953);
    timer = &D_80148654;
    if (TIMER_EXPIRED(*timer)) {
        i = 0;
        while (i < Party_CountOrder(PARTY_ORDER_KIND_WALKING)) {
            /* FAKE: retail reads g_MenuPanelTasks[0].unk_0B as u8[]. */
            ((u8*)&D_8014833B)[((i + 4) * 9) << 2] = 1;
            i++;
        }
        timer = &D_80148652;
        (*timer)++;
    }
}
