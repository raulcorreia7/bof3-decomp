#include "magic138_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

/* Blocker: copies 16 halfwords from 0x80036C00 to 0x8003AC00 (unnamed data, no table yet) and swaps the scratchpad work pointer to g_BattleEffectBattler around func_8014D978. */
INCLUDE_ASM(func_801EEC88);

INCLUDE_ASM(func_801EED60);

MATCH void func_801EEED8(void) {
    PartyBattler* saved_work;

    saved_work = g_Task;
    g_Task     = g_BattleEffectBattler;
    func_8014D978();
    g_Task = saved_work;
    if (saved_work->param.unk_0B == 0) {
        func_800A9820(g_BattleTargetSelector);
        g_BattleState |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}

MATCH void func_801EEF60(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

MATCH void func_801EEFA4(void) {
    EffectStepFuncs3 handlers;

    handlers     = D_801EEC10;
    g_ScriptBank = 0x800C3800;
    SYS_DISPATCH_TASK(handlers.handlers, 2, g_Task);
    if (g_Task->header.flags & 1) {
        Area_AddActor();
    }
    g_ScriptBank = 0x800D3800;
}

INCLUDE_ASM(func_801EF04C);

INCLUDE_ASM(func_801EF3A0);

MATCH void func_801EF50C(void) {
    func_801E5988();
}

/* blocker: constant register; first diff: 0x801EF554 (retail holds 0x800F0800 in v0 and g_Task in v1). */
MATCH void func_801EF52C(void) {
    EffectStepFuncs3 handlers;

    handlers     = D_801EEC1C;
    g_ScriptBank = 0x800F0800;
    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        func_8014D290();
    }
    g_ScriptBank = 0x800D3800;
}

MATCH void func_801EF5D0(void) {
    PartyBattler* work;
    g_Task->unk_29    = 0;
    g_Task->unk_25    = 0x1D;
    g_Task->unk_26    = 0;
    g_Task->unk_24    = 0x84;
    g_Task->unk_27    = 0xB4;
    g_Task->unk_28    = 0;
    work              = g_Task;
    work->unk_2B      = 0;
    work->unk_2C.half = 0;
    g_Task->unk_2A    = 0;
    Actor_SelectScript(5);
    SND_PlayCue((g_Task->timer & 1) | 0x100);
    g_Task->header.step += 1;
}

MATCH void func_801EF6A4(void) {
    if (func_8014D978() != 0u) {
        g_Task->header.step = g_Task->header.step + 1;
    } else {
        Area_AddActor();
    }
}

#include "overlays/bmagic/Effect_TickDownAndClear.h"
