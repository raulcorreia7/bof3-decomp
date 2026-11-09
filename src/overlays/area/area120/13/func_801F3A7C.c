#include "area120_13.h"

MATCH void func_801F3A7C(void) {
    s16 index;

    index               = g_Task->pos.x.part.integer;
    g_Task->pos.x.fixed = D_801F4404[index * 2] << 16;
    g_Task->pos.y.fixed = D_801F4405[index * 2] << 16;
    g_Task->vx          = (s32)(D_801EB748 + index * 0x118);
    g_Task->timer       = 0;
    g_Task->unk_0A      = 0;
    g_Task->header.step += 1;
    func_801F3F5C(0x80, 0x40, 1, 0);
}
