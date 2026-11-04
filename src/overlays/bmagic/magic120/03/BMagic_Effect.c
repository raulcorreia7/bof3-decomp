#include "magic120_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC70);

INCLUDE_ASM(func_801EEEC8);

#include "overlays/bmagic/Effect_PlayOnIdleTick.h"

MATCH void func_801EF010(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EF054);

INCLUDE_ASM(func_801EF0D8);

/* Template: bmagic/magic040 func_801EF114; size 0x6C against retail 0x7C, first difference lbu v0,9(v1) at +0x0C. */
INCLUDE_ASM(func_801EF270);

#include "overlays/bmagic/Effect_CountUpTimerCallSelector.h"

#include "overlays/bmagic/Effect_CountUpAndStepAt120.h"

MATCH void func_801EF3C4(void) {
    u8 counter;

    g_SpadWork->word_08.byte.unk_0B += 1;
    g_SpadWork->unk_04 -= 1;
    counter                         = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.unk_09 = counter;
    if ((counter & 0xFF) == 0x88) {
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B = 0xFF;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF44C);

INCLUDE_ASM(func_801EFD20);

INCLUDE_ASM(func_801EFDD4);

MATCH void func_801F0008(void) {
    func_8014D290();
    if (func_8014DAEC() & BYTE_MASK) {
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F0044);

MATCH void func_801F009C(void) {
    u8 timer;

    func_801F0274();
    timer                           = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 0x60) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

INCLUDE_ASM(func_801F0104);

MATCH void func_801F0158(void) {
    u8 timer;

    func_801F08AC();
    timer                           = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 0x10) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

MATCH void func_801F01C0(void) {
    u8 count;

    func_801F08AC();
    count                             = g_SpadWork->word_08.byte.timer_0A - 1;
    g_SpadWork->word_08.byte.timer_0A = count;
    if (count == 0) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

INCLUDE_ASM(func_801F0224);

INCLUDE_ASM(func_801F0274);

INCLUDE_ASM(func_801F04B0);

INCLUDE_ASM(func_801F078C);

INCLUDE_ASM(func_801F08AC);

INCLUDE_ASM(func_801F0974);

#include "overlays/bmagic/Effect_SetActorMatrix.h"
