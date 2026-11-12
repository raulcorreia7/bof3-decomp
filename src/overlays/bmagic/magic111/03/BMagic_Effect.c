#include "magic111_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

INCLUDE_ASM(func_801EEC7C);

MATCH void func_801EEF44(void) {
    if (g_Task->param.unk_0B == 0) {
        func_800AEF98(4, 0);
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Task->header.mode += 1;
    }
}

#include "shared/Effect_StartPlaying.h"

/* func_801EEFF8 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF03C(void) {
    Magic111Steps handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        func_8014D290();
    }
}

MATCH void func_801EF0C0(void) {
    PartyMember* work;

    work              = g_Task;
    work->unk_29      = 2;
    work              = g_Task;
    work->header.step = (work->header.step + 1);
}

MATCH void func_801EF0F0(void) {
    u8           step;
    PartyMember* work;

    work = (PartyMember*)g_BattleEffectBattler;
    step = work->param.unk_0B;
    if (step < 2) {
        work->param.unk_0B  = step - 1;
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EF138(void) {
    func_801E5988();
}

MATCH void func_801EF158(void) {
    SYS_DISPATCH_BYTE(D_801EFAA8, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        g_Task->unk_0C++;
        g_Task->unk_10++;
        func_801EF330();
    }
}

MATCH void func_801EF1D4(void) {
    s32 start;

    start          = RANDOM_MASK(0x3F);
    g_Task->unk_0C = start;
    g_Task->unk_10 = start + 0x1F;
    g_Task->unk_09 = 0;
    g_Task->timer  = 60;
    g_Task->header.step += 1;
}

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_CountDownAndStep.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801EF330);

MATCH void func_801EF7F8(void) {
    SYS_DISPATCH_BYTE(D_801EFAB8, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EF970();
    }
}

MATCH void func_801EF870(void) {
    if (g_BattleEffectBattler->param.unk_0B < 3U) {
        g_Task->unk_09 = 0;
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_CountUpByTwoAndStep.h"

MATCH void Effect_TickOnTimerZero2(void) {
    PartyMember* work;

    BMAGIC_TICK_ON_TIMER_ZERO(2);
}

INCLUDE_ASM(func_801EF970);
