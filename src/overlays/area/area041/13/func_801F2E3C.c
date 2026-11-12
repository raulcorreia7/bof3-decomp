#include "area041_13.h"

MATCH void func_801F2E3C(void) {
    g_Task->timer++;
    g_Task->pos.y.fixed += 8;
    if (g_Task->timer >= 32) {
        g_Task->header.step++;
        Area_SetCellCode(41, D_801F42C8[g_Task->param.unk_0B], 0);
        Area_SetCellCode(41, D_801F42C8[g_Task->param.unk_0B] + 1, 0);
    }
    func_801F2EFC();
}
