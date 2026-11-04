#include "magic096_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC84);

MATCH void func_801EEDD8(void) {
    u8 timer;

    timer                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 0) {
        func_800A9610(g_BattleTargetSelector, 0x200);
        g_SpadWork->step_01 = g_SpadWork->step_01 + 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEEA0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EEEE4);

INCLUDE_ASM(func_801EEFB8);

INCLUDE_ASM(func_801EF2CC);

MATCH void func_801EF348(void) {
    u8 timer;

    timer                           = g_SpadWork->word_08.byte.unk_0B - 1;
    g_SpadWork->word_08.byte.unk_0B = timer;
    if (timer == 0) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

#include "overlays/bmagic/Effect_CountDownTimerStep.h"

MATCH void func_801EF3E0(void) {
    PartyBattler* work;

    work                      = g_SpadWork;
    work->word_08.byte.unk_0A = work->word_08.byte.unk_0A - 1;
    if (work->word_08.byte.unk_0A == 0) {
        work                      = (PartyBattler*)D_801EB4E0;
        work->word_08.byte.unk_0B = work->word_08.byte.unk_0B - 1;
        func_801E5988();
    }
}

MATCH void func_801EF43C(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = g_SpadWork->unk_18;
    rot.vy = g_SpadWork->unk_1C;
    rot.vz = 0;
    BMAGIC_PROJECT_ACTOR_MATRIX(g_SpadWork);
}

INCLUDE_ASM(func_801EF4FC);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EFB3C);

INCLUDE_ASM(func_801EFDF4);

INCLUDE_ASM(func_801F0164);
