#include "area134_13.h"

MATCH u8* func_801F4938(void) {
    u8* p;
    u8  i;

    p = MEM_PTR(u8, AREA_WORK);
    for (i = 0; i < 32; i++) {
        if (p[0] == 0) {
            return p;
        }
        p += 0x28;
    }
    return NULL;
}
