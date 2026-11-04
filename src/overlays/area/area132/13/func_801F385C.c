#include "area132_13.h"

MATCH void func_801F385C(void) {
    u8 i;

    D_801F4A88 = MEM_PTR(u8, AREA_WORK);
    i          = 0u;
    do {
        D_801F4A88[0] = 0u;
        D_801F4A88 += 0x18;
        i += 1u;
    } while (i < 32u);
}
