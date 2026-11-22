#include "shop_00.h"

MATCH void func_801DE45C(void) {
    u8* timer;
    u8  count;

    Menu_DrawClutStrip(g_WindowClut);
    func_801DEE64();
    timer = &D_80148654;
    if (TIMER_EXPIRED(*timer)) {
        count      = D_80148651;
        *timer     = 3;
        D_80148651 = count + 1;
    }
}
