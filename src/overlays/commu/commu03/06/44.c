#include "commu03_06.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The commu03 overlay entry: the shared commu step byte selects the handler. */
MATCH void func_801D0C44(void) {
    SYS_DISPATCH_BYTE(g_Commu03States, D_801F294C);
}

MATCH void func_801D0C80(void) {
    SYS_DISPATCH_BYTE(g_Commu03Step0Funcs, D_801F294D);
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
    SYS_DISPATCH_BYTE(g_Commu03Step1Funcs, D_801F294D);
}

INCLUDE_ASM(func_801D0E28);

INCLUDE_ASM(func_801D1000);

MATCH void func_801D1058(void) {
    SYS_DISPATCH_BYTE(g_Commu03Step2Funcs, D_801F294D);
}

MATCH void func_801D1094(void) {
    s32 bgm_offset;

    if (g_SndBGMId != BGM_NONE) {
        if (g_SndBGMId != D_801D1944) {
            bgm_offset = g_SndBGMId * 4;
            SND_StopSequence(*(g_SelectionCues + bgm_offset), *(D_80181EBB + bgm_offset));
        }
    }
    SND_RequestBGM(D_801D1944);
    func_801D1250(0x32, 0x28);
    D_801F294D += 1;
}

MATCH void func_801D1124(void) {
    if (EMI_IsReady() != 0) {
        SND_PlayBGM(D_801D1944, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
        D_801D1948 = 0;
        D_801F294D += 1;
    }
    func_801D1250(0x32, 0x28);
}

MATCH void func_801D1184(void) {
    u8 count;

    count      = D_801D1948 + 1;
    D_801D1948 = count;
    func_801D1250(0x32, (s16)(0x28 - count * 0x32));
    if (D_801D1948 == 4) {
        Message_StartAreaMessage(0x5A);
        g_GameStateIndex = GAME_REQUEST_MESSAGE;
        D_801F294D += 1;
    }
}

#include "overlays/commu/Fairy_EndCommuScene.h"

INCLUDE_ASM(func_801D1250);

INCLUDE_ASM(func_801D1714);

MATCH void func_801D18AC(void) {
    u8* state;

    state = &g_SceneEventStep;
    *state += 1;
}
