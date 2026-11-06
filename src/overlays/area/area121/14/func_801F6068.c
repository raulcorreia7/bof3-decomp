#include "area121_14.h"

MATCH void func_801F6068(void) {
    u8 temp_v0;

    temp_v0 = g_Task->unk_0A;
    if (temp_v0 == 0) {
        g_Task->pos.x.fixed = *D_80145EC4;
        ORDER_FENCE(); /* FAKE: the order fence keeps the x load with its store. */
        g_Task->pos.y.fixed = D_80145EC8;
        g_Task->pos.z.fixed = D_80145ECC + 0x800000;
        func_801F60F4(g_Task);
        g_Task->header.mode += 1;
        return;
    }
    g_Task->unk_0A = temp_v0 - 1;
}
