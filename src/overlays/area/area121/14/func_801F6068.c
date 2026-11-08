#include "area121_14.h"

MATCH void func_801F6068(void) {
    u8 count;

    count = g_Task->unk_0A;
    if (count == 0) {
        g_Task->pos.x.fixed = *D_80145EC4;
        FAKE_ORDER_FENCE(); /* FAKE: the order fence keeps the x load with its store. */
        g_Task->pos.y.fixed = D_80145EC8;
        g_Task->pos.z.fixed = D_80145ECC + TO_COORD(128);
        func_801F60F4(g_Task);
        g_Task->header.mode += 1;
        return;
    }
    g_Task->unk_0A = count - 1;
}
