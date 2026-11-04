#include "magic130_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC70);

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEED4(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EEF18);

INCLUDE_ASM(func_801EEFB4);

INCLUDE_ASM(func_801EF10C);

#include "overlays/bmagic/Effect_CountDownTimerStep.h"

INCLUDE_ASM(func_801EF1E0);

INCLUDE_ASM(func_801EF284);

INCLUDE_ASM(func_801EF354);

MATCH void func_801EF3DC(void) {
    u8 timer;

    timer                             = g_SpadWork->word_08.byte.timer_0A + 1;
    g_SpadWork->word_08.byte.timer_0A = timer;
    if (timer == 16) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

MATCH void Effect_CountDownTimerStep_801EF42C(void) {
    u8 timer;

    BMAGIC_COUNT_DOWN_TIMER_STEP();
}

#include "overlays/bmagic/Effect_CountDownAndFinish.h"

INCLUDE_ASM(func_801EF4D4);

INCLUDE_ASM(func_801EF730);
