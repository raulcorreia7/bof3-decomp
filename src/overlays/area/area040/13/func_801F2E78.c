#include "area040_13.h"

MATCH s32 func_801F2E78(void) {
    s32 value;
    s32 value2;
    s32 i;
    s32 j;

    if ((D_80144EA9 & 0xF) == 5) {
        i = 0;
        do {
            value = (i & BYTE_MASK) + 3;
            func_801A4BC0(65, value, 0);
            func_801A4BC0(66, value, 0);
            func_801A4BC0(67, value, 0);
            func_801A4BC0(68, value, 0);
            i += 1;
        } while ((i & BYTE_MASK) < 7U);
        return 1;
    }
    j = 0;
    do {
        value2 = (j & BYTE_MASK) + 3;
        func_801A4BC0(65, value2, 0xA4);
        func_801A4BC0(66, value2, 0xA4);
        func_801A4BC0(67, value2, 0xA4);
        func_801A4BC0(68, value2, 0xA4);
        j += 1;
    } while ((j & BYTE_MASK) < 7U);
    return 0;
}
