#include "area145_14.h"

MATCH void func_801F2D44(void) {
    u8 i;

    for (i = 0; i < 4; i++) {
        g_Task->vx     = (D_801F543C[i].x1 << 16) | 0x8000;
        g_Task->vy     = (D_801F543C[i].y1 << 16) | 0x8000;
        g_Task->unk_18 = (D_801F543C[i].x2 << 16) | 0x8000;
        g_Task->unk_1C = (D_801F543C[i].y2 << 16) | 0x8000;
        func_801F2F30(&g_Task->vx, &g_Task->unk_18);
    }
    D_801F544C[g_Task->header.step]();
}
