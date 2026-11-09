#include "area174_13.h"

/* The first row of the area174 work window whose byte at +0x03 is clear, or
 * NULL. The counter is 16-bit here, unlike the shared body's u8 member. */

MATCH u8* func_801F2E88(void) {
    u8* p;
    u16 i;

    p = MEM_PTR(u8, AREA_WORK);
    for (i = 0; i < 32; i++) {
        if (p[3] == 0) {
            return p;
        }
        p += 0x2C;
    }
    return NULL;
}
