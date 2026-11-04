#include "sce15ef1_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801D0C0C(void) {
    /* FAKE: retail reads the handler record from entry $v0; the pin is the
       entry-register residual (identical bytes to the unpinned 84.46%). */
    MATCH_REG(u8*, entity, "v0");

    D_801D3918[entity[1]]();
}

INCLUDE_ASM(func_801D0C48);

INCLUDE_ASM(func_801D0CC0);

INCLUDE_ASM(func_801D0D54);

INCLUDE_ASM(func_801D0DD8);

INCLUDE_ASM(func_801D0F10);

INCLUDE_ASM(func_801D0FEC);

INCLUDE_ASM(func_801D106C);

INCLUDE_ASM(func_801D12A0);

INCLUDE_ASM(func_801D13F4);

INCLUDE_ASM(func_801D147C);

INCLUDE_ASM(func_801D1678);

MATCH void func_801D199C(void) {
    s32 var_v1_6;
    s8* var_a0_5;

    var_a0_5 = &D_801D39A8;
    var_v1_6 = 0;
    do {
        *var_a0_5 = 0;
        var_v1_6 += 1;
        var_a0_5 += 0x18;
    } while ((u32)(var_v1_6 & BYTE_MASK) < 0x10U);
}

INCLUDE_ASM(func_801D19C8);

INCLUDE_ASM(func_801D1A60);

INCLUDE_ASM(func_801D1B10);

INCLUDE_ASM(func_801D1CD4);

#include "shared/Area_InitSpin.h"

INCLUDE_ASM(func_801D2088);

MATCH void func_801D2138(s32* first, s32* second) {
    s32 temp_v0_7;
    s32 temp_v1_11;

    temp_v0_7  = *first ^ *second;
    *first     = temp_v0_7;
    temp_v1_11 = *second ^ temp_v0_7;
    *second    = temp_v1_11;
    *first ^= temp_v1_11;
}

MATCH void func_801D2170(void) {
    SYS_DISPATCH_TASK(D_801D3954, 1, g_SpadWork);
}

INCLUDE_ASM(func_801D21B4);

INCLUDE_ASM(func_801D23A0);

INCLUDE_ASM(func_801D2474);

INCLUDE_ASM(func_801D26BC);

INCLUDE_ASM(func_801D2934);

MATCH void func_801D2B44(void) {
    Actor_Clear();
}

MATCH void func_801D2B64(void) {
    SYS_DISPATCH_TASK(D_801D396C, 1, g_SpadWork);
}

INCLUDE_ASM(func_801D2BA8);

INCLUDE_ASM(func_801D2C00);

INCLUDE_ASM(func_801D2C94);

/* nonmatching: step of the actor position (func_801D36BC(&x, unk_0C, unk_10)), then unk_0C += unk_18, unk_10 += unk_1C, unk_09--, unk_18 -= 0x100, unk_1C -= 0x200, Actor_Clear at zero. Three statement orders tried; best differs from retail at +0x2C (retail loads lbu a1,9(v1) first, candidate lw v0,12(v1)). */
INCLUDE_ASM(func_801D2D5C);

MATCH void func_801D2DEC(void) {
    SYS_DISPATCH_TASK(D_801D397C, 1, g_SpadWork);
}

INCLUDE_ASM(func_801D2E30);

INCLUDE_ASM(func_801D2FD8);

INCLUDE_ASM(func_801D30AC);

INCLUDE_ASM(func_801D32F4);

INCLUDE_ASM(func_801D34F0);

MATCH void func_801D369C(void) {
    Actor_Clear();
}

INCLUDE_ASM(func_801D36BC);
