#include "area174_13.h"

/* The area174 rows are 0x2C bytes apart; the byte this overlay clears is at
 * +0x03. The counter is 16-bit here, unlike the shared body's u8 member. */

MATCH void func_801F2E5C(void) {
    u8* p;
    u16 i;

    p = MEM_PTR(u8, AREA_WORK);
    i = 0;
    do {
        p[3] = 0;
        i++;
        p += 0x2C;
    } while (i < 32);
}
