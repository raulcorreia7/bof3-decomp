#include "magic146_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC10);

INCLUDE_ASM(func_801EED18);

#include "overlays/bmagic/Effect_NextStepOnZeroTick.h"

#include "shared/Effect_PlayOnce.h"

MATCH void func_801EF04C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
}

MATCH void func_801EF090(void) {
    SYS_DISPATCH_TASK(D_801EF9B8, 2, g_SpadWork);
}

INCLUDE_ASM(func_801EF0D4);

#include "overlays/bmagic/Effect_FinishOnZeroTick.h"

MATCH void func_801EF2FC(void) {
    SYS_DISPATCH_TASK(D_801EF9C0, 1, g_SpadWork);
}

MATCH void func_801EF340(void) {
    SYS_DISPATCH_BYTE(D_801EF9C4, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801EF604();
    }
}

INCLUDE_ASM(func_801EF3B8);

#include "overlays/bmagic/Effect_CountUpTimersByTwoNextStep.h"

MATCH void func_801EF58C(void) {
    PartyBattler* work;
    PartyBattler* active;
    u8            count;

    work = g_SpadWork;
    work->word_08.byte.unk_09++;
    work                        = g_SpadWork;
    count                       = work->word_08.byte.timer_0A - 1;
    work->word_08.byte.timer_0A = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->word_08.byte.unk_0B--;
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801EF604);

/* func_801EF900 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801EF964 */
MATCH void Actor_Clear(void) {
    Bmagic_ResetLocalWork();
}
