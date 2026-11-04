#include "magic124_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC14);

INCLUDE_ASM(func_801EEDD8);

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

INCLUDE_ASM(func_801EEFF0);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

INCLUDE_ASM(func_801EF0B0);

MATCH void func_801EF268(void) {
}

MATCH void func_801EF270(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EF2B4);

INCLUDE_ASM(func_801EF3FC);

MATCH void func_801EF588(void) {
    u8 timer;

    timer              = g_SpadWork->unk_0A + 4;
    g_SpadWork->unk_0A = timer;
    if (timer == 16) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

INCLUDE_ASM(func_801EF5D8);

INCLUDE_ASM(func_801EF654);

INCLUDE_ASM(func_801EF6E8);

MATCH void func_801F020C(void) {
    SYS_DISPATCH_BYTE(D_801F08F4, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801F03E0();
        func_801F05B4();
    }
}

MATCH void func_801F028C(void) {
    g_SpadWork->unk_5D = 8;
    g_SpadWork->unk_5E = 6;
    g_SpadWork->unk_5F = 15;
    g_SpadWork->unk_09 = 0;
    g_SpadWork->unk_0A = 2;
    g_SpadWork->unk_02++;
}

MATCH void func_801F02FC(void) {
    PartyBattler* work;

    work = g_SpadWork;
    work->unk_0A += 2;
    work = g_SpadWork;
    work->unk_09 += 4;
    if (work->unk_09 == 16) {
        work = g_SpadWork;
        work->unk_02++;
    }
}

MATCH void func_801F0368(void) {
    PartyBattler* work;
    u8            count;

    work = g_SpadWork;
    work->unk_0A++;
    work         = g_SpadWork;
    count        = work->unk_09 - 4;
    work->unk_09 = count;
    if (count == 0) {
        BATTLE_ACTIVE_WORK->unk_0B--;
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801F03E0);

INCLUDE_ASM(func_801F05B4);

/* func_801F0828 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F088C */
MATCH void Actor_Clear(void) {
    Bmagic_ResetLocalWork();
}
