#include "area041_13.h"

MATCH void func_801F2C48(void) {
    u8 idx;

    g_Task->param.unk_0B = g_Task->pos.x.part.integer;
    idx                  = g_Task->param.unk_0B;
    if (SYS_TestFlag(&g_SceneFlagWords[D_801F42CC[idx] * 8], D_801F42D0[idx])) {
        g_Task->header.step = 3;
        g_Task->pos.y.fixed = D_801F42C8[g_Task->param.unk_0B] + 2;
    } else {
        g_Task->header.step++;
        g_Task->pos.y.fixed = D_801F42C8[g_Task->param.unk_0B];
        func_801A4BC0(0x29, D_801F42C8[g_Task->param.unk_0B], 0x50);
        func_801A4BC0(0x29, D_801F42C8[g_Task->param.unk_0B] + 1, 0x50);
    }
    g_Task->pos.x.fixed = -0x2B80;
    g_Task->pos.y.fixed = (g_Task->pos.y.fixed << 7) - 0x4040;
    func_801F2EFC();
    func_801F3064();
}
