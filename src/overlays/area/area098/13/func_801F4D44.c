#include "area098_13.h"

MATCH void func_801F4D44(void) {
    u8* p;
    u8  i;

    p = MEM_PTR(u8, AREA_WORK);
    i = 0;
    do {
        p[0] = 0;
        i++;
        p += 0x1C;
    } while (i < 16);
    D_801F6510 = 0;
    D_801F6514 = 0;
}
