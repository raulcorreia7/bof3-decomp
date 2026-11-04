#include "magic067_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC24(void) {
    BattleHandlerTable5 handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_TASK(handlers.handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EEC94);

#include "overlays/bmagic/Effect_CountDownTimerCallSelector.h"

MATCH void func_801EEFA4(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 0) {
        func_800A9820(g_BattleTargetSelector);
        g_SpadWork->word_08.byte.unk_09 = 0x1E;
        g_SpadWork->step_01 += 1;
    }
}

INCLUDE_ASM(func_801EF010);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH void func_801EF2D0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EF314(void) {
    SYS_DISPATCH_BYTE(D_801F04C8, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0) {
        func_801EF688();
        func_801EF79C();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF38C);

INCLUDE_ASM(func_801EF44C);

INCLUDE_ASM(func_801EF4F4);

#include "overlays/bmagic/Effect_DriftStep.h"

INCLUDE_ASM(func_801EF688);

INCLUDE_ASM(func_801EF79C);

MATCH void func_801EFF24(void) {
    D_801F04D8[g_SpadWork->unk_02]();
    if (g_SpadWork->flags_00 != 0) {
        func_801F00C4();
    }
}

#include "overlays/bmagic/Effect_ArmCounterNextStep.h"

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_CountDownAndStep.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801F00C4);

MATCH void func_801F02A0(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectFuncs + 12, 2, g_SpadWork);
}

MATCH void func_801F02E4(void) {
    func_800AEEC8(g_SpadWork->unk_04, g_SpadWork->unk_03);
    g_SpadWork->word_08.byte.unk_0B = 1;
    g_SpadWork->unk_02 += 1;
}

#include "overlays/bmagic/Effect_TickOnZeroTick.h"

MATCH void func_801F038C(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC18;
    SYS_DISPATCH_TASK(handlers.handlers, 2, g_SpadWork);
}

MATCH void func_801F03EC(void) {
    g_SpadWork->word_08.byte.unk_0B = 0;
    g_SpadWork->word_08.byte.unk_09 = 0;
    Actor_SelectScript(3);
    g_SpadWork->unk_02++;
}

#include "overlays/bmagic/Effect_AddActorStepOnPlaying.h"

MATCH void func_801F0498(void) {
    func_801E5988();
}
