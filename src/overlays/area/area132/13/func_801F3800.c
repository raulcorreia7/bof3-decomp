#include "area132_13.h"

MATCH s32 func_801F3800(void) {
    u8 i;

    D_801F4A88 = MEM_PTR(u8, AREA_WORK);
    i          = 0u;
    do {
        if (D_801F4A88[0] != 0u) {
            D_801F4A88 += 0x18;
            i += 1u;
        } else {
            return (s32)D_801F4A88;
        }
    } while (i < 32u);
    return 0;
}
