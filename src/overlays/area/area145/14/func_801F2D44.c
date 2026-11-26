#include "area145_14.h"

MATCH void func_801F2D44(void) {
    u8 i;

    for (i = 0; i < 4; i++) {
        SELF(Actor)->vx     = (D_801F543C[i].x0 << 16) | 0x8000;
        SELF(Actor)->vy     = (D_801F543C[i].y0 << 16) | 0x8000;
        SELF(Actor)->unk_18 = (D_801F543C[i].x1 << 16) | 0x8000;
        SELF(Actor)->unk_1C = (D_801F543C[i].y1 << 16) | 0x8000;
        func_801F2F30(&SELF(Actor)->vx, &SELF(Actor)->unk_18);
    }
    D_801F544C[SELF(Actor)->header.step]();
}
