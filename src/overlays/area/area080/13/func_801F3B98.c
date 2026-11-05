#include "area080_13.h"

MATCH void* func_801F3B98(void) {
    u8 i;

    D_801F44A4 = (s8*)(AREA_WORK + 0x6C);
    i          = 0u;
    do {
        if (((u8*)D_801F44A4)[0] != 0u) {
            D_801F44A4 += 0x60;
            i += 1u;
        } else {
            return D_801F44A4;
        }
    } while (i < 8u);

    return 0;
}
