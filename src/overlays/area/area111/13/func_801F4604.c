#include "area111_13.h"

MATCH void func_801F4604(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_s4;

    temp_s1 = (s32)(arg0 << 0x10) >> 0xF;
    temp_s4 = temp_s1 + 0xB;
    temp_s0 = (s32)(arg1 << 0x10) >> 0xF;
    temp_s3 = temp_s0 + 0xB1;
    temp_s2 = arg2 & 0xFF;
    func_801A4BC0(temp_s4, temp_s3, temp_s2);
    temp_s1_2 = temp_s1 + 0xC;
    func_801A4BC0(temp_s1_2, temp_s3, temp_s2);
    temp_s0_2 = temp_s0 + 0xB2;
    func_801A4BC0(temp_s4, temp_s0_2, temp_s2);
    func_801A4BC0(temp_s1_2, temp_s0_2, temp_s2);
}
