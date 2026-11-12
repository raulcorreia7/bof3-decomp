#include "magic067_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC24(void) {
    Magic067Steps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Task);
}

INCLUDE_ASM(func_801EEC94);

#include "overlays/bmagic/Effect_CountDownTimerCallSelector.h"

MATCH void func_801EEFA4(void) {
    if (g_Task->param.phase == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Task->unk_09 = 0x1E;
        g_Task->header.mode += 1;
    }
}

INCLUDE_ASM(func_801EF010);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

/* func_801EF2D0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF314(void) {
    SYS_DISPATCH_BYTE(D_801F04C8, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        func_801EF688();
        func_801EF79C();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF38C);

MATCH void func_801EF44C(void) {
    s32 count;
    u8  count_next;

    count = g_Task->param.phase + 1;
    count += g_Task->unk_09 >> 6;
    g_Task->param.phase = count;
    if (g_FrameCount & 1) {
        g_Task->timer += 1;
    }
    count_next     = g_Task->unk_09 + 2;
    g_Task->unk_09 = count_next;
    if ((count_next & BYTE_MASK) == 0xC0) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF4F4(void) {
    s32 count;
    u8  count_next;

    count = g_Task->param.phase + 1;
    count += g_Task->unk_09 >> 6;
    g_Task->param.phase = count;
    if (g_FrameCount & 1) {
        g_Task->timer -= 1;
    }
    count_next     = g_Task->unk_09 - 2;
    g_Task->unk_09 = count_next;
    if ((count_next & BYTE_MASK) == 0x60) {
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_Drift.h"

INCLUDE_ASM(func_801EF688);

INCLUDE_ASM(func_801EF79C);

MATCH void func_801EFF24(void) {
    D_801F04D8[g_Task->header.step]();
    if (g_Task->header.flags != 0) {
        func_801F00C4();
    }
}

#include "overlays/bmagic/Effect_ArmCounterNextStep.h"

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_CountDownAndStep.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801F00C4);

MATCH void func_801F02A0(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectModes + 12, 2, g_Task);
}

#include "overlays/bmagic/Effect_QueueEntry.h"

#include "overlays/bmagic/Effect_TickOnZeroTick.h"

MATCH void func_801F038C(void) {
    Magic067SecondSteps handlers;

    handlers = D_801EEC18;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Task);
}

MATCH void func_801F03EC(void) {
    g_Task->param.phase = 0;
    g_Task->unk_09      = 0;
    Actor_SelectScript(3);
    g_Task->header.step++;
}

#include "overlays/bmagic/Effect_AddActor.h"

MATCH void func_801F0498(void) {
    func_801E5988();
}
