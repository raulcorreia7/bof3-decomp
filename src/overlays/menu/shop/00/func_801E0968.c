#include "shop_00.h"

MATCH void func_801E0968(void) {
    u8* delay_ptr;
    u8  count;

    delay_ptr = &D_80148654;
    if (TIMER_EXPIRED(*delay_ptr)) {
        g_UIPanelTasks[5].panel  = 7;
        g_UIPanelTasks[5].mode   = 0xE;
        g_UIPanelTasks[5].active = 1;
        g_UIPanelTasks[5].unk_0B = 0xFF;
        g_UIPanelTasks[5].pos.vx = 0xC8;
        g_UIPanelTasks[5].unk_0A = 0;
        g_UIPanelTasks[5].pos.vy = 0x3F;
        count                    = D_80148652;
        D_80148652               = count + 1;
    }
}
