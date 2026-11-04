#include "magic167_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC1C.h"

INCLUDE_ASM(func_801EEC94);

MATCH void func_801EEE88(void) {
    PartyBattler** selected;

    if (--g_SpadWork->unk_09 == 0) {
        selected           = &g_BattleSelectedActor;
        GFX_FreePaletteFadeTarget(*selected);
        g_SpadWork->unk_0A = GFX_AllocPaletteFade((u8*)*selected, 0, 0, 0, 1);
        g_SpadWork->unk_09 = 8;
        g_SpadWork->step_01++;
    }
}

INCLUDE_ASM(func_801EEF38);

MATCH void func_801EF048(void) {
    PartyBattler* work;

    work = g_SpadWork;
    if (work->unk_0B < 2) {
        work->step_01++;
    }
}

INCLUDE_ASM(func_801EF080);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801EF2D8(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EF31C);

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_StepWhileTickUnderTwo.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801EF4B0);

INCLUDE_ASM(func_801EF708);

INCLUDE_ASM(func_801EF9B8);

MATCH void func_801EFA70(void) {
    u8 timer;

    timer              = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = timer;
    if (timer == 0) {
        g_SpadWork->unk_0A = 0x1;
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

INCLUDE_ASM(func_801EFACC);

INCLUDE_ASM(func_801EFB5C);

MATCH void func_801EFBE4(void) {
    PartyBattler* work;
    u8            next;

    work         = g_SpadWork;
    next         = work->unk_0A + 1;
    work->unk_0A = next;
    if (next == 0x18) {
        D_801EB4E0->unk_0B--;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EFC44);

INCLUDE_ASM(func_801F05C8);
