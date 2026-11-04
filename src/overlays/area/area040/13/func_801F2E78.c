#include "area040_13.h"

MATCH s32 func_801F2E78(void) {
    s32 value;
    s32 value2;
    s32 i;
    s32 j;

    if ((D_80144EA9 & 0xF) == 5) {
        i = 0;
        do {
            value = (i & 0xFF) + 3;
            func_801A4BC0(0x41, value, 0);
            func_801A4BC0(0x42, value, 0);
            func_801A4BC0(0x43, value, 0);
            func_801A4BC0(0x44, value, 0);
            i += 1;
        } while ((u32)(i & 0xFF) < 7U);
        return 1;
    }
    j = 0;
    do {
        value2 = (j & 0xFF) + 3;
        func_801A4BC0(0x41, value2, 0xA4);
        func_801A4BC0(0x42, value2, 0xA4);
        func_801A4BC0(0x43, value2, 0xA4);
        func_801A4BC0(0x44, value2, 0xA4);
        j += 1;
    } while ((u32)(j & 0xFF) < 7U);
    return 0;
}
