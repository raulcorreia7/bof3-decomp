#include "area120_13.h"

MATCH void func_801F3630(void) {
    u8* p;
    u16 i;

    p = MEM_PTR(u8, AREA_WORK_WINDOW_ADDRESS);
    for (i = 0; i < AREA_ROW_COUNT; i++) {
        if (p[0] == 0) {
            p[0] = 1;
            p[2] = 0;
            p[3] = D_801F43E4;
            D_801F43E4 ^= 1;
            return;
        }
        p += AREA_ROW_STRIDE;
    }
}
