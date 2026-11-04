#include "area040_13.h"

MATCH s32 func_801F2E78(void) {
    s32 temp_s0;
    s32 temp_s0_2;
    s32 var_s1;
    s32 var_s1_2;

    if ((D_80144EA9 & 0xF) == 5) {
        var_s1 = 0;
        do {
            temp_s0 = (var_s1 & 0xFF) + 3;
            func_801A4BC0(0x41, temp_s0, 0);
            func_801A4BC0(0x42, temp_s0, 0);
            func_801A4BC0(0x43, temp_s0, 0);
            func_801A4BC0(0x44, temp_s0, 0);
            var_s1 += 1;
        } while ((u32)(var_s1 & 0xFF) < 7U);
        return 1;
    }
    var_s1_2 = 0;
    do {
        temp_s0_2 = (var_s1_2 & 0xFF) + 3;
        func_801A4BC0(0x41, temp_s0_2, 0xA4);
        func_801A4BC0(0x42, temp_s0_2, 0xA4);
        func_801A4BC0(0x43, temp_s0_2, 0xA4);
        func_801A4BC0(0x44, temp_s0_2, 0xA4);
        var_s1_2 += 1;
    } while ((u32)(var_s1_2 & 0xFF) < 7U);
    return 0;
}
