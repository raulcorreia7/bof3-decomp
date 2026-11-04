#include "area047_13.h"

MATCH void func_801F32C4(void) {
    u8* p;
    u8  i;

    p = MEM_PTR(u8, AREA_WORK_WINDOW_ADDRESS);
    for (i = 0; i < AREA_ROW_COUNT; i++) {
        if (p[AREA_ROW_FLAG_OFFSET] == 0) {
            p[AREA_ROW_FLAG_OFFSET] = 1;
            p[AREA_ROW_FLAG_OFFSET + 1] = 0;
            return;
        }
        p += AREA_ROW_STRIDE;
    }
}
