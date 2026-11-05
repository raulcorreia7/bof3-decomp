#include "magic111_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC7C);

MATCH void func_801EEF44(void) {
    if (g_Task->word_08.byte.unk_0B == 0) {
        func_800AEF98(4, 0);
        BATTLE_ACTIVE_WORK->flags &= 0xBF;
        func_800A9820(g_BattleTargetSelector);
        g_Task->mode += 1;
    }
}

#include "shared/Effect_StartPlaying.h"

MATCH void func_801EEFF8(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

MATCH void func_801EF03C(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->step);
    if (g_Task->flags != 0) {
        func_8014D290();
    }
}

MATCH void func_801EF0C0(void) {
    PartyBattler* work;

    work         = g_Task;
    work->unk_29 = 2;
    work         = g_Task;
    work->step   = (u8)(work->step + 1);
}

MATCH void func_801EF0F0(void) {
    u8            step;
    PartyBattler* work;

    work = (PartyBattler*)D_801EB4E0;
    step = work->word_08.byte.unk_0B;
    if (step < 2) {
        work->word_08.byte.unk_0B = step - 1;
        g_Task->step              = g_Task->step + 1;
    }
}

MATCH void func_801EF138(void) {
    func_801E5988();
}

INCLUDE_ASM(func_801EF158);

MATCH void func_801EF1D4(void) {
    s32 start;

    start                         = rand() & 0x3F;
    g_Task->unk_0C                = start;
    g_Task->unk_10                = start + 0x1F;
    g_Task->word_08.byte.unk_09   = 0;
    g_Task->word_08.byte.timer_0A = 0x3C;
    g_Task->step += 1;
}

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_CountDownAndStep.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801EF330);

MATCH void func_801EF7F8(void) {
    SYS_DISPATCH_BYTE(D_801EFAB8, g_Task->step);
    if (g_Task->flags != 0 && g_Task->step != 0) {
        func_801EF970();
    }
}

MATCH void func_801EF870(void) {
    if ((u8)D_801EB4E0->word_08.byte.unk_0B < 3U) {
        g_Task->word_08.byte.unk_09 = 0;
        g_Task->step += 1;
    }
}

#include "overlays/bmagic/Effect_CountUpByTwoAndStep.h"

MATCH void Effect_TickOnTimerZero_801EF914(void) {
    PartyBattler* work;

    BMAGIC_TICK_ON_TIMER_ZERO(2);
}

INCLUDE_ASM(func_801EF970);
