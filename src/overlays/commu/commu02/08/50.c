#include "commu02_08.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The commu02 overlay entry: the shared commu step byte selects the handler. */
MATCH void func_801D0C50(void) {
    SYS_DISPATCH_BYTE(g_Commu02Event0States, D_801F294C);
}

MATCH void func_801D0C8C(void) {
    SYS_DISPATCH_BYTE(g_Commu02Event0Step0Funcs, D_801F294D);
}

/* blocker: constant and store order; first diff: 801D0CD0. */
INCLUDE_ASM(func_801D0CC8);

MATCH void func_801D0D54(void) {
    if (EMI_IsReady() != 0) {
        SND_PlayBGM(BGM_COMMU02, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
        D_801F294D = 0;
        D_801F294C += 1;
    }
}

MATCH void func_801D0DA4(void) {
    SYS_DISPATCH_BYTE(g_Commu02Event0Step1Funcs, D_801F294D);
}

MATCH void func_801D0DE0(void) {
    s8 count;
    u8 check;

    if (D_801F294E == 0) {
        D_801DB0C4 = 4;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x02));
        D_801F294E += 1;
        return;
    }
    count      = D_801DB0C4 - 1;
    D_801DB0C4 = count;
    func_801D3184(0x6E - ((count & 0xFF) * 0x28), 0x48);
    func_801D32A0(0x6E - ((u8)D_801DB0C4 * 0x28), 0x74, 1);
    check = D_801DB0C4;
    if (check == 0) {
        Message_StartAreaMessage(0x71);
        g_GameStateIndex = GAME_REQUEST_MESSAGE;
        D_801DB07C       = 0;
        D_801DB0B4       = 0;
        D_801F294E       = 0;
        D_801F294D += 1;
    }
}

MATCH void func_801D0EEC(void) {
    func_801D3184(0x6E, 0x48);
    func_801D32A0(0x6E, 0x74, 1);
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        D_801F294D += 1;
    }
}

MATCH void func_801D0F4C(void) {
    SYS_DISPATCH_BYTE(g_Commu02Event0Step1Sub2Funcs, D_801F294E);
}
