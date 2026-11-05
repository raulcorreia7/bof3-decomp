#include "magic137_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC7C);

#include "overlays/bmagic/Effect_CountDownTimerCallSelector.h"

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

MATCH void func_801EF174(void) {
    PartyBattler* work = g_SpadWork;
    u8            count;
    u8            phase = work->word_08.byte.unk_0B;
    u8            timer;
    phase += 1;
    timer                     = work->word_08.byte.unk_09;
    work->word_08.byte.unk_0B = phase + (timer >> 6);
    if (g_FrameCount & 1) {
        g_SpadWork->word_08.byte.timer_0A += 1;
    }
    count                           = g_SpadWork->word_08.byte.unk_09 + 2;
    g_SpadWork->word_08.byte.unk_09 = count;
    if (count == 0xC0) {
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EF21C(void) {
    PartyBattler* work = g_SpadWork;
    u8            count;
    u8            phase = work->word_08.byte.unk_0B;
    u8            timer;
    phase += 1;
    timer                     = work->word_08.byte.unk_09;
    work->word_08.byte.unk_0B = phase + (timer >> 6);
    if (g_FrameCount & 1) {
        g_SpadWork->word_08.byte.timer_0A -= 1;
    }
    count                           = g_SpadWork->word_08.byte.unk_09 - 2;
    g_SpadWork->word_08.byte.unk_09 = count;
    if (count == 0x60) {
        g_SpadWork->unk_02 += 1;
    }
}

#include "overlays/bmagic/Effect_DriftStep.h"

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

#include "../../Effect_DispatchHandlerSlot2.h"

MATCH void func_801F001C(void) {
    g_SpadWork->word_08.byte.unk_0B = 0;
    g_SpadWork->word_08.byte.unk_09 = 0;
    Actor_SelectScript(3);
    func_8014D978();
    Area_AddActor();
    g_SpadWork->unk_02++;
}

#include "overlays/bmagic/Effect_AddActorStepOnPlaying.h"

MATCH void func_801F00D8(void) {
    func_801E5988();
}
