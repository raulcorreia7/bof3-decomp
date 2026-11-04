#include "magic173_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EED90};

    SYS_DISPATCH_TASK(handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEDF0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EEE34);

INCLUDE_ASM(func_801EEEEC);

INCLUDE_ASM(func_801EF148);

INCLUDE_ASM(func_801EF3D8);

MATCH void func_801EF484(void) {
    u8 timer;

    func_801F03A0();
    timer                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 0) {
        BMAGIC_TICK_EFFECT_WORK();
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF4EC);

INCLUDE_ASM(func_801EFA34);

MATCH void func_801F02B0(void) {
    s32 i;

    BMAGIC_SHIFT_TRAIL(D_801F09B0)
    D_801F09B0[g_SpadWork->unk_04][g_SpadWork->word_08.byte.unk_0B].x = g_SpadWork->unk_2E.half;
    D_801F09B0[g_SpadWork->unk_04][g_SpadWork->word_08.byte.unk_0B].y = g_SpadWork->unk_30.half;
}

MATCH void func_801F03A0(void) {
    s32 i;

    BMAGIC_SHIFT_TRAIL(D_801F09B0)
    D_801F09B0[g_SpadWork->unk_04][g_SpadWork->word_08.byte.unk_0B].x = -1;
    D_801F09B0[g_SpadWork->unk_04][g_SpadWork->word_08.byte.unk_0B].y = -1;
}

INCLUDE_ASM(func_801F0488);

INCLUDE_ASM(func_801F0540);

MATCH void func_801F0648(void) {
    u8 timer;

    func_8014DAEC();
    timer                           = g_SpadWork->word_08.byte.unk_09 + 4;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 0x10) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

MATCH void func_801F06B0(void) {
    func_8014DAEC();
    if (func_8014DAEC() != 0u) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

#include "overlays/bmagic/Effect_TickOnTimerZero.h"
INCLUDE_ASM(func_801F075C);
