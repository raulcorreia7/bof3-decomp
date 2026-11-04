#include "magic137_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC7C);

MATCH void func_801EEEFC(void) {
    u8 timer;

    timer                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 0) {
        func_800A9610(g_BattleTargetSelector, 0x20);
        g_SpadWork->step_01 = g_SpadWork->step_01 + 1;
    }
}

MATCH void func_801EEF64(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 0) {
        func_800A9820(g_BattleTargetSelector);
        g_SpadWork->word_08.byte.unk_09 = 30;
        g_BattleState |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}

MATCH void func_801EEFD4(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EF018(void) {
    SYS_DISPATCH_BYTE(D_801F0104, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0) {
        func_801EF3B0();
        func_801EF4C4();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF090);

INCLUDE_ASM(func_801EF174);

INCLUDE_ASM(func_801EF21C);

MATCH void func_801EF2C4(void) {
    PartyBattler* work;
    u8            timer;
    u8            ticks;

    BMAGIC_DRIFT_EFFECT_STEP()
}

INCLUDE_ASM(func_801EF3B0);

INCLUDE_ASM(func_801EF4C4);

MATCH void func_801EFC58(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 7), 2, g_SpadWork);
    if (g_SpadWork->flags_00 != 0) {
        func_801EFDF8();
    }
}

#include "overlays/bmagic/Effect_ArmCounterNextStep.h"

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_CountDownAndStep.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801EFDF8);

MATCH void func_801EFFBC(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_TASK(handlers.handlers, 2, g_SpadWork);
}

MATCH void func_801F001C(void) {
    g_SpadWork->word_08.byte.unk_0B = 0;
    g_SpadWork->word_08.byte.unk_09 = 0;
    Actor_SelectScript(3);
    func_8014D978();
    Area_AddActor();
    g_SpadWork->unk_02++;
}

MATCH void func_801F007C(void) {
    func_8014D978();
    Area_AddActor();
    if (g_BattleState & BATTLE_STATE_EFFECT_PLAYING) {
        g_SpadWork->unk_02++;
    }
}

MATCH void func_801F00D8(void) {
    func_801E5988();
}
