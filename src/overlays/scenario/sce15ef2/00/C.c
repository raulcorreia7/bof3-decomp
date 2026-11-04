#include "sce15ef2_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801D0C0C);

MATCH void func_801D0C70(void) {
    u8* work;
    u8* step;

    work                  = (u8*)g_SpadWork;
    work[9]               = 0x10;
    step                  = (u8*)g_SpadWork;
    FIELD(s32, work, 0xC) = 0;
    step[1]++;
}

INCLUDE_ASM(func_801D0CA0);

MATCH void func_801D0D00(void) {
    u8 timer;

    timer                        = ((Actor*)g_SpadWork)->unk_09 - 1;
    ((Actor*)g_SpadWork)->unk_09 = timer;
    if (timer == 0) {
        ((Actor*)g_SpadWork)->unk_09 = 0x10;
        ((Actor*)g_SpadWork)->unk_01 = ((Actor*)g_SpadWork)->unk_01 + 1;
    }
}

INCLUDE_ASM(func_801D0D5C);

MATCH void func_801D0DA4(void) {
    SYS_DISPATCH_TASK(D_801D1B2C, 1, g_SpadWork);
}

MATCH void func_801D0DE8(void) {
    Actor* work;

    work         = (Actor*)g_SpadWork;
    work->unk_2E = 300;
    work->unk_09 = 0;
    func_801D15B0();
    ((Actor*)g_SpadWork)->unk_01 = ((Actor*)g_SpadWork)->unk_01 + 1;
}

INCLUDE_ASM(func_801D0E30);

MATCH void func_801D0EC4(void) {
    if (!(func_801D1624(0xF0) & BYTE_MASK)) {
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801D0EF8);

MATCH void func_801D0F68(void) {
    Actor* work;

    work                         = (Actor*)g_SpadWork;
    work->unk_09                 = 10;
    work->unk_2E                 = 0;
    work->unk_30                 = 0;
    ((Actor*)g_SpadWork)->unk_01 = ((Actor*)g_SpadWork)->unk_01 + 1;
}

INCLUDE_ASM(func_801D0F9C);

INCLUDE_ASM(func_801D1008);

INCLUDE_ASM(func_801D1050);

MATCH void func_801D10A4(void) {
    SYS_DISPATCH_TASK(D_801D1B48, 1, g_SpadWork);
}

MATCH void func_801D10E8(void) {
    u8* work;

    work    = (u8*)g_SpadWork;
    work[9] = 0x10;
    work    = (u8*)g_SpadWork;
    work[1]++;
}

INCLUDE_ASM(func_801D1118);

INCLUDE_ASM(func_801D11A4);

INCLUDE_ASM(func_801D1218);

INCLUDE_ASM(func_801D1414);

MATCH void func_801D15B0(void) {
    s32 index;
    s8* cell;

    cell  = (s8*)AREA_WORK_WINDOW;
    index = 0;
    do {
        *cell = 0;
        index += 1;
        cell += 6;
    } while ((u32)(index & BYTE_MASK) < 0x10U);
}

INCLUDE_ASM(func_801D15DC);

/* Walks the 16 six-byte slots at 0x800E4800 and returns 1 when one is active. A slot in state 0 takes `countdown` into its
 * halfword at +2; in state 2 that halfword drops by 8 per call and the slot is released once it goes negative. */
INCLUDE_ASM(func_801D1624);

INCLUDE_ASM(func_801D17A0);

INCLUDE_ASM(func_801D19A8);
