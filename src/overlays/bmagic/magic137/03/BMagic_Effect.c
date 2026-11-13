#include "magic137_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

INCLUDE_ASM(func_801EEC7C);

#include "overlays/bmagic/Effect_CountDownTimerCallSelector.h"

MATCH void func_801EEF64(void) {
    if (g_Task->param.phase == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Task->unk_09 = 30;
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}

/* func_801EEFD4 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF018(void) {
    SYS_DISPATCH_BYTE(D_801F0104, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Effect_SetFacingMatrix();
        func_801EF4C4();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF090);

MATCH void func_801EF174(void) {
    PartyMember* work = g_Task;
    u8           count;
    u8           phase = work->param.phase;
    u8           timer;
    phase += 1;
    timer             = work->unk_09;
    work->param.phase = phase + (timer >> 6);
    if (g_FrameCount & 0x1) {
        g_Task->timer += 1;
    }
    count          = g_Task->unk_09 + 2;
    g_Task->unk_09 = count;
    if (count == 192) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF21C(void) {
    PartyMember* work = g_Task;
    u8           count;
    u8           phase = work->param.phase;
    u8           timer;
    phase += 1;
    timer             = work->unk_09;
    work->param.phase = phase + (timer >> 6);
    if (g_FrameCount & 0x1) {
        g_Task->timer -= 1;
    }
    count          = g_Task->unk_09 - 2;
    g_Task->unk_09 = count;
    if (count == 96) {
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_Drift.h"

#include "overlays/bmagic/Effect_SetFacingMatrix.h"

INCLUDE_ASM(func_801EF4C4);

MATCH void func_801EFC58(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 7), 2, g_Task);
    if (g_Task->header.flags != 0) {
        func_801EFDF8();
    }
}

#include "overlays/bmagic/Effect_ArmCounterNextStep.h"

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_CountDownAndStep.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801EFDF8);

#include "overlays/bmagic/Effect_DispatchStep.h"

MATCH void func_801F001C(void) {
    g_Task->param.phase = 0;
    g_Task->unk_09      = 0;
    Actor_SelectScript(3);
    Actor_StepAnimLoop();
    Area_AddActor();
    g_Task->header.step++;
}

#include "overlays/bmagic/Effect_AddActor.h"

MATCH void func_801F00D8(void) {
    func_801E5988();
}
