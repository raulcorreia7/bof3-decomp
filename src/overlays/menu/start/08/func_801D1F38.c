#include "start_08.h"

MATCH void func_801D1F38(void) {
    u8* timer;

    Menu_DrawClutStrip(D_80144953);
    timer = &D_80148654;
    if (TIMER_EXPIRED(*timer)) {
        *timer              = 5;
        g_MenuStep.sub_step = 0;
        g_MenuStep.state    = 0;
        D_80148653          = 0;
        g_MenuStep.step     = D_80148655 + 2;
    }
}
