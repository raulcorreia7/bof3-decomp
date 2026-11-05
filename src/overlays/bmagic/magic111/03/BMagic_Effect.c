#include "magic111_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC7C);

MATCH void func_801EEF44(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 0) {
        func_800AEF98(4, 0);
        BATTLE_ACTIVE_WORK->flags_00 &= 0xBF;
        func_800A9820(g_BattleTargetSelector);
        g_SpadWork->step_01 += 1;
    }
}

#include "shared/Effect_StartPlaying.h"

MATCH void func_801EEFF8(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EF03C(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_BYTE(handlers.handlers, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0) {
        func_8014D290();
    }
}

MATCH void func_801EF0C0(void) {
    PartyBattler* work;

    work         = g_SpadWork;
    work->unk_29 = 2;
    work         = g_SpadWork;
    work->unk_02 = (u8)(work->unk_02 + 1);
}

MATCH void func_801EF0F0(void) {
    u8            step;
    PartyBattler* work;

    work = (PartyBattler*)D_801EB4E0;
    step = work->word_08.byte.unk_0B;
    if (step < 2) {
        work->word_08.byte.unk_0B = step - 1;
        g_SpadWork->unk_02        = g_SpadWork->unk_02 + 1;
    }
}

MATCH void func_801EF138(void) {
    func_801E5988();
}

INCLUDE_ASM(func_801EF158);

MATCH void func_801EF1D4(void) {
    s32 start;

    start                             = rand() & 0x3F;
    g_SpadWork->unk_0C                = start;
    g_SpadWork->unk_10                = start + 0x1F;
    g_SpadWork->word_08.byte.unk_09   = 0;
    g_SpadWork->word_08.byte.timer_0A = 0x3C;
    g_SpadWork->unk_02 += 1;
}

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_CountDownAndStep.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801EF330);

MATCH void func_801EF7F8(void) {
    SYS_DISPATCH_BYTE(D_801EFAB8, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801EF970();
    }
}

INCLUDE_ASM(func_801EF870);

#include "overlays/bmagic/Effect_CountUpByTwoAndStep.h"

MATCH void Effect_TickOnTimerZero_801EF914(void) {
    PartyBattler* work;

    BMAGIC_TICK_ON_TIMER_ZERO(2);
}

INCLUDE_ASM(func_801EF970);
