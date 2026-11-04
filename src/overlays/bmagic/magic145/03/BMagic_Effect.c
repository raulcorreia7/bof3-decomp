#include "magic145_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC70);

MATCH void func_801EEDB0(void) {
    PartyBattler* work;

    work = g_SpadWork;
    if (work->word_08.byte.unk_0B == 0) {
        work->step_01++;
    }
}

#include "shared/Effect_PlayOnce.h"

MATCH void func_801EEE2C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EEE70(void) {
    SYS_DISPATCH_BYTE(D_801EF418, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801EF118();
    }
}

INCLUDE_ASM(func_801EEEE8);

#include "overlays/bmagic/Effect_CountUpTimersByTwoNextStep.h"

#include "overlays/bmagic/Effect_CountDownTimer.h"

INCLUDE_ASM(func_801EF118);
