#include "area117_13.h"

MATCH void func_801F33F8(void) {
    g_Task->param.unk_0B = COORD_INT(g_Task->pos.x);
    g_Task->pos.x.fixed  = D_801F4658[g_Task->param.unk_0B * 2] << 16;
    g_Task->pos.y.fixed  = D_801F4659[g_Task->param.unk_0B * 2] << 16;
    if (SYS_TestFlag(D_80144ED0, D_801F463C[g_Task->param.unk_0B])) {
        g_Task->header.step++;
        func_801F34C8();
    } else {
        g_Task->header.step = 3;
        func_801F364C();
    }
}
