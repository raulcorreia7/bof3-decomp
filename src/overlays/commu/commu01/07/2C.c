#include "commu01_07.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The commu01 overlay entry: the shared commu step byte selects the handler. */
MATCH void func_801D0C2C(void) {
    SYS_DISPATCH_BYTE(g_Commu01States, D_801F294C);
}

MATCH void func_801D0C68(void) {
    D_801D4DF4 = 1;
    D_801D4DF8 = 0;
    D_801D4DFC = 0;
    D_801D4E0C = 181;
    D_801F294C++;
}

INCLUDE_ASM(func_801D0CAC);

MATCH void func_801D0E44(void) {
    SYS_DISPATCH_BYTE(g_Commu01Step2Funcs, D_801D4E08);
}

MATCH void func_801D0E80(void) {
    SYS_DISPATCH_BYTE(D_801D4BE4, D_801F294D);
}

INCLUDE_ASM(func_801D0EBC);

INCLUDE_ASM(func_801D1158);

MATCH void func_801D1328(void) {
    SYS_DISPATCH_BYTE(g_Commu01Step2Sub1Funcs, D_801F294D);
}

INCLUDE_ASM(func_801D1364);

MATCH void func_801D1630(void) {
    u16 x;
    s16 y;
    s32 result;
    u8* selection;

    result = 0;
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        func_801D47C4();
        func_801D49C4();
    } else if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        result = func_801D482C(1);
        if (result & 0xFF) {
            D_801D4E0C = 0xB5;
        }
    } else {
        func_801D3B0C(&D_801D4E28);
        func_801D4AAC(&D_801D4E28);
    }
    func_801D3038();
    selection = &g_SceneEventSelection;
    func_801D36FC(*selection, 1);
    func_801D36FC(D_801D4E28, 0);
    if (!(result & 0xFF)) {
        func_801D4694(&x, &y, *selection, D_801D4E24);
        func_801D3984((s16)(x + 4), y, 1);
        func_801D28A4(0xA0, 0x3E, func_801D3AA0(*selection, (D_801D4E24 - 1) & 0xFF) & 0xFF, 1);
    }
}

INCLUDE_ASM(func_801D1778);

INCLUDE_ASM(func_801D1A94);

INCLUDE_ASM(func_801D1E48);

INCLUDE_ASM(func_801D2110);

/* First difference: s5 is saved as s6. */
INCLUDE_ASM(func_801D273C);

INCLUDE_ASM(func_801D28A4);

INCLUDE_ASM(func_801D2D98);

INCLUDE_ASM(func_801D3038);

INCLUDE_ASM(func_801D3594);

INCLUDE_ASM(func_801D36FC);

/* First difference: s2 is saved as s1. */
INCLUDE_ASM(func_801D3984);

INCLUDE_ASM(func_801D3A48);

INCLUDE_ASM(func_801D3AA0);

INCLUDE_ASM(func_801D3B0C);

INCLUDE_ASM(func_801D3EFC);

INCLUDE_ASM(func_801D4030);

INCLUDE_ASM(func_801D4178);

INCLUDE_ASM(func_801D42DC);

/* needs: Area_SampleHeight result type; first diff: +0x60 early return. */
INCLUDE_ASM(func_801D4474);

INCLUDE_ASM(func_801D44E0);

INCLUDE_ASM(func_801D4694);

MATCH void func_801D47C4(void) {
    D_801D4DF4 = D_801D4E00;
    D_801D4DF8 = D_801D4E04;
    D_801D4DFC = D_801D4E08;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
    D_801F294D--;
}

INCLUDE_ASM(func_801D482C);

/* needs: typed 18-byte lookup data and fairy room access. */
INCLUDE_ASM(func_801D49C4);

INCLUDE_ASM(func_801D4AAC);

MATCH void func_801D4B58(void) {
    D_801D4E10 = D_801F294D;
    D_801D4E14 = D_801D4E0C;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
    D_801D4E0C = 61;
    D_801D4E18 = 0;
    D_801F294D = 5;
}
