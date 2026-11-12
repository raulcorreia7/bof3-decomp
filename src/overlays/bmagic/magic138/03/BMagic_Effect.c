#include "magic138_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

INCLUDE_ASM(func_801EEC88);

INCLUDE_ASM(func_801EED60);

MATCH void func_801EEED8(void) {
    PartyMember* saved_work;

    saved_work = g_Task;
    g_Task     = g_BattleEffectBattler;
    Actor_StepAnimLoop();
    g_Task = saved_work;
    if (saved_work->param.unk_0B == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}

/* func_801EEF60 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEFA4(void) {
    Magic138Steps handlers;

    handlers      = D_801EEC10;
    g_ScriptTable = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Task);
    if (g_Task->header.flags & 1) {
        Area_AddActor();
    }
    g_ScriptTable = AREA_SCRIPT_TABLE;
}

INCLUDE_ASM(func_801EF04C);

INCLUDE_ASM(func_801EF3A0);

MATCH void func_801EF50C(void) {
    func_801E5988();
}

MATCH void func_801EF52C(void) {
    Magic138Steps handlers;

    handlers      = D_801EEC1C;
    g_ScriptTable = BATTLE_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        func_8014D290();
    }
    g_ScriptTable = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF5D0(void) {
    PartyMember* work;
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
    if (Actor_StepAnimLoop() != 0u) {
        g_Task->header.step = g_Task->header.step + 1;
    } else {
        Area_AddActor();
    }
}

#include "overlays/bmagic/Effect_TickDownAndClear.h"
