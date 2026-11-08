#include "magic130_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

INCLUDE_ASM(func_801EEC70);

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEED4(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

MATCH void func_801EEF18(void) {
    g_ScriptBank = 0x800C3800;
    D_801EFA4C[g_Task->header.step]();
    if ((g_Task->header.flags & 1) && (g_Task->header.step != 0)) {
        func_8014D290();
    }
    g_ScriptBank = AREA_SCRIPT_BANK;
}

/* blocker: work pointer lifetime; first diff: lui v1 at +0x20. */
INCLUDE_ASM(func_801EEFB4);

MATCH void func_801EF10C(void) {
    g_Task->unk_5D += 8;
    g_Task->unk_5E += 8;
    g_Task->unk_5F += 8;
    if ((s8)g_Task->unk_5D == 0) {
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_CountDownTimerStep.h"

MATCH void func_801EF1E0(void) {
    g_Task->unk_5D -= 8;
    g_Task->unk_5E -= 8;
    g_Task->unk_5F -= 8;
    if ((s8)g_Task->unk_5D == -0x80) {
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EF284(void) {
    SYS_DISPATCH_BYTE(D_801EFA5C, g_Task->header.step);
    GFX_AddDitheredDrawMode(2, getTPage(0, 1, 320, 256));
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EF4D4();
        func_801EF730();
    }
}

MATCH void func_801EF354(void) {
    PartyMember* task;
    u16          value;

    task              = g_Task;
    task->unk_2E.half = task->param.unk_0B * 26 + 0x98;
    value             = D_801EFA6C[task->param.unk_0B];
    task->unk_14      = 0x20;
    task->unk_09      = 0x3C;
    task->unk_30.half = value + 0x50;
    g_Task->timer     = 0;
    g_Task->header.step += 1;
}

MATCH void func_801EF3DC(void) {
    u8 timer;

    timer         = g_Task->timer + 1;
    g_Task->timer = timer;
    if (timer == 16) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void Effect_CountDownTimerStep2(void) {
    BMAGIC_COUNT_DOWN_TIMER_STEP();
}

#include "overlays/bmagic/Effect_CountDownAndFinish.h"

INCLUDE_ASM(func_801EF4D4);

INCLUDE_ASM(func_801EF730);
