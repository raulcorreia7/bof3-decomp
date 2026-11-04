#include "commu03_06.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The commu03 overlay entry: the shared commu step byte selects the handler. */
MATCH void func_801D0C44(void) {
    SYS_DISPATCH_BYTE(D_801D18C8, D_801F294C);
}

MATCH void func_801D0C80(void) {
    SYS_DISPATCH_BYTE(D_801D18D4, D_801F294D);
}

INCLUDE_ASM(func_801D0CBC);

MATCH void func_801D0D60(void) {
    u8 value;

    value      = D_801D1948 - 1;
    D_801D1948 = value;
    func_801D1250(0x32, (s16)(0x28 - ((value & 0xFF) * 0x32)));
    if (D_801D1948 == 0) {
        D_801F294D = 0;
        D_801F294C += 1;
    }
}

MATCH void func_801D0DEC(void) {
    SYS_DISPATCH_BYTE(D_801D18DC, D_801F294D);
}

INCLUDE_ASM(func_801D0E28);

INCLUDE_ASM(func_801D1000);

MATCH void func_801D1058(void) {
    SYS_DISPATCH_BYTE(D_801D18E4, D_801F294D);
}

INCLUDE_ASM(func_801D1094);

INCLUDE_ASM(func_801D1124);

MATCH void func_801D1184(void) {
    u8 count;

    count      = D_801D1948 + 1;
    D_801D1948 = count;
    func_801D1250(0x32, (s16)(0x28 - count * 0x32));
    if (D_801D1948 == 4) {
        Message_StartAreaMessage(0x5A);
        g_GameStateIndex = 2;
        D_801F294D += 1;
    }
}

#include "overlays/commu/Commu_AdvanceStep.h"

INCLUDE_ASM(func_801D1250);

INCLUDE_ASM(func_801D1714);

MATCH void func_801D18AC(void) {
    u8* state;

    state = &D_801448EC;
    *state += 1;
}
