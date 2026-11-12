#include "magic052_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

MATCH void func_801EEC7C(void) {
    PartyMember* work;

    g_Task->unk_09    = 8;
    g_Task->timer     = 4;
    work              = g_Task;
    work->header.mode = work->header.mode + 1;
}

INCLUDE_ASM(func_801EECBC);

MATCH void func_801EEE30(void) {
    if (g_Task->timer-- == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}

MATCH void func_801EEE94(void) {
    Callback handlers[2];

    handlers[0] = func_801EEEE0;
    handlers[g_Task->header.mode]();
}

MATCH void func_801EEEE0(void) {
    Magic052Steps handlers = D_801EEC10;

    g_ScriptTable = BATTLE_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        func_8014D290();
    }
    g_ScriptTable = AREA_SCRIPT_TABLE;
}

MATCH void func_801EEF84(void) {
    PartyMember* work;
    s32          cue;
    u8           timer;

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
    timer             = g_Task->unk_09;
    if (timer != 0) {
        cue = 0x100;
        if (timer & 1) {
            cue = 0x101;
        }
    } else {
        cue = 0x102;
    }
    SND_QueueSelectionFx(cue);
    Actor_SelectScript(5U);
    g_Task->header.step += 1;
}

MATCH void func_801EF070(void) {
    PartyMember* work;

    if (Actor_StepAnimLoop() != 0u) {
        work              = g_Task;
        work->header.step = work->header.step + 1;
    } else {
        Area_AddActor();
    }
}

MATCH void func_801EF0C4(void) {
    func_801E5988();
}
