#include "magic041_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC38(void) {
    BattleHandlerTable6 handlers = D_801EEC04;

    SYS_DISPATCH_TASK(handlers.handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EECB0);

INCLUDE_ASM(func_801EEE14);

INCLUDE_ASM(func_801EEEB4);

MATCH void func_801EEFC4(void) {
    PartyBattler* work;

    work = SP_REF(PartyBattler*, 0x44u);
    if (work->word_08.byte.unk_0B == 1) {
        work->step_01 = work->step_01 + 1;
    }
}

INCLUDE_ASM(func_801EEFF8);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EF190(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EF1D4(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC1C;
    SYS_DISPATCH_BYTE(handlers.handlers, g_SpadWork->unk_02);
    if (ACTOR_IN_USE(*g_SpadWork) && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801EF670();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF27C);

MATCH void func_801EF308(void) {
    u8 timer;

    timer                             = g_SpadWork->word_08.byte.timer_0A + 4;
    g_SpadWork->word_08.byte.timer_0A = timer;
    if (timer == 32) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

MATCH void func_801EF358(void) {
    PartyBattler* work;
    PartyBattler* active;
    u8            count;

    work = g_SpadWork;
    work->word_08.byte.unk_09 += 4;
    work                        = g_SpadWork;
    count                       = work->word_08.byte.timer_0A - 1;
    work->word_08.byte.timer_0A = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->word_08.byte.unk_0B--;
        func_801E5988();
    }
}

MATCH void func_801EF3D0(void) {
    MagicTaskFuncs handlers;

    handlers = D_801EEC28;
    SYS_DISPATCH_BYTE(handlers.handlers, g_SpadWork->unk_02);
    if (ACTOR_IN_USE(*g_SpadWork) && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801EFAB8();
        PopMatrix();
    }
}

MATCH void func_801EF484(void) {
    PartyBattler* src;

    src                             = (PartyBattler*)D_801EB4E0;
    g_SpadWork->coord_x_34          = src->coord_x_34;
    g_SpadWork->coord_y_38          = src->coord_y_38;
    g_SpadWork->word_3C             = src->word_3C;
    g_SpadWork->word_08.byte.unk_09 = 0;
    g_SpadWork->unk_02              = g_SpadWork->unk_02 + 1;
}

#include "overlays/bmagic/Effect_CountUpByTwoAndStep.h"

#include "overlays/bmagic/Effect_NextStepOnLastTick.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF670);

INCLUDE_ASM(func_801EFAB8);
