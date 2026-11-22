#include "area145_14.h"

MATCH void func_801F2D44(void) {
    u8 i;

    for (i = 0; i < 4; i++) {
        TASK(Actor)->vx     = (D_801F543C[i].x0 << 16) | 0x8000;
        TASK(Actor)->vy     = (D_801F543C[i].y0 << 16) | 0x8000;
        TASK(Actor)->unk_18 = (D_801F543C[i].x1 << 16) | 0x8000;
        TASK(Actor)->unk_1C = (D_801F543C[i].y1 << 16) | 0x8000;
        func_801F2F30(&TASK(Actor)->vx, &TASK(Actor)->unk_18);
    }
    D_801F544C[TASK(Actor)->header.step]();
}
