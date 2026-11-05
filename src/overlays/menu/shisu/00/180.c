#include "shisu_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The shisu overlay entry: the shared menu step byte selects the handler. */
MATCH void func_801D0D80(void) {
    SYS_DISPATCH_BYTE(D_801D96DC, D_80148650);
}

INCLUDE_ASM(func_801D0DBC);

MATCH void func_801D0E4C(void) {
    SYS_DISPATCH_BYTE(D_801D96F0, D_80148651);
}

MATCH void func_801D0E88(void) {
    u8* counter;

    UI_SetMode(3);
    func_801D1D1C();
    counter = &D_80148651;
    *counter += 1;
}

INCLUDE_ASM(func_801D0EC4);

MATCH void func_801D0F24(void) {
    SYS_DISPATCH_BYTE(D_801D96F8, D_80148651);
}

INCLUDE_ASM(func_801D0F60);

INCLUDE_ASM(func_801D0FAC);

INCLUDE_ASM(func_801D1018);

MATCH void func_801D11A4(void) {
    func_801D7224(D_80144953);
    D_801D9700[D_80148651]();
}

INCLUDE_ASM(func_801D11F4);

INCLUDE_ASM(func_801D14C0);

MATCH void func_801D1898(void) {
    Callback handler;

    handler = D_801D970C[D_80148652];
    handler();
    func_801D2C0C();
    func_801D2DA8();
}

MATCH void func_801D18E4(void) {
    u8* count;
    u8  value;

    count      = &D_80148652;
    value      = *count;
    D_801DA0C1 = 2;
    D_801DA049 = 2;
    *count     = value + 1;
}

INCLUDE_ASM(func_801D1910);

INCLUDE_ASM(func_801D1964);

INCLUDE_ASM(func_801D1A20);

INCLUDE_ASM(func_801D1B58);

MATCH void func_801D1CA4(void) {
    D_801DA028 = Party_CountItem(0, 77, 0);
    D_801DA029 = Party_CountItem(0, 35, 0);
    D_801DA02A = Party_CountItem(0, 36, 0);
    D_801DA02B = Party_CountItem(0, 86, 0);
}

/* Tried: store-seq body with the status block declared in shisu_00.h.
 * GCC loads the first store constant (li v0,20) first; retail hoists
 * li v1,1 and li a0,2 before it. First diff +0x00: li v0,20.
 */
INCLUDE_ASM(func_801D1D1C);

MATCH void func_801D1E34(void) {
    FIELD(u8, g_MenuPanelTasks, 0) = 0;
    D_80148357                     = 1;
    D_8014837B                     = 1;
    D_8014839F                     = 1;
}

INCLUDE_ASM(func_801D1E60);

INCLUDE_ASM(func_801D1EE8);

INCLUDE_ASM(func_801D2308);

INCLUDE_ASM(func_801D27BC);

INCLUDE_ASM(func_801D2978);
