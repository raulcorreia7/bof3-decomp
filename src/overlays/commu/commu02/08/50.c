#include "commu02_08.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The commu02 overlay entry: the shared commu step byte selects the handler. */
MATCH void func_801D0C50(void) {
    SYS_DISPATCH_BYTE(D_801DABCC, D_801F294C);
}

MATCH void func_801D0C8C(void) {
    SYS_DISPATCH_BYTE(D_801DABD8, D_801F294D);
}

INCLUDE_ASM(func_801D0CC8);

MATCH void func_801D0D54(void) {
    if (EMI_LoaderIsReady() != 0) {
        SND_PlayBgm(0x94, 0x64, 8);
        D_801F294D = 0;
        D_801F294C += 1;
    }
}

MATCH void func_801D0DA4(void) {
    SYS_DISPATCH_BYTE(D_801DABE0, D_801F294D);
}

INCLUDE_ASM(func_801D0DE0);

MATCH void func_801D0EEC(void) {
    func_801D3184(0x6E, 0x48);
    func_801D32A0(0x6E, 0x74, 1);
    if (g_GameStateIndex != 2) {
        D_801F294D += 1;
    }
}

MATCH void func_801D0F4C(void) {
    SYS_DISPATCH_BYTE(D_801DAC14, D_801F294E);
}
