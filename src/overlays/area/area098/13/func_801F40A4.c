#include "area098_13.h"

MATCH void func_801F40A4(void) {
    u8* p;
    u8  i;

    p = MEM_PTR(u8, AREA_WORK);
    i = 0;
    do {
        p[0] = 0;
        i++;
        p += 0x38;
    } while (i < 24);
}
