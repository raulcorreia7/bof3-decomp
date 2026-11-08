#include "magic052_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

MATCH void func_801EEC7C(void) {
    PartyBattler* work;

    g_Task->unk_09    = 8;
    g_Task->timer     = 4;
    work              = g_Task;
    work->header.mode = work->header.mode + 1;
}

INCLUDE_ASM(func_801EECBC);

MATCH void func_801EEE30(void) {
    if (g_Task->timer-- == 0) {
        func_800A9820(g_BattleTargetSelector);
        g_BattleState |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}

MATCH void func_801EEE94(void) {
    Callback handlers[2];

    handlers[0] = func_801EEEE0;
    handlers[TASK_BYTES[1]]();
}

MATCH void func_801EEEE0(void) {
    EffectStepFuncs3 handlers = D_801EEC10;

    g_ScriptBank = 0x800F0800;
    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        func_8014D290();
    }
    g_ScriptBank = AREA_SCRIPT_BANK;
}

MATCH void func_801EEF84(void) {
    PartyBattler* work;
    s32           var_a0;
    u8            temp_v0;

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
    temp_v0           = g_Task->unk_09;
    if (temp_v0 != 0) {
        var_a0 = 0x100;
        if (temp_v0 & 1) {
            var_a0 = 0x101;
        }
    } else {
        var_a0 = 0x102;
    }
    SND_QueueSelectionFx(var_a0);
    Actor_SelectScript(5U);
    g_Task->header.step += 1;
}

MATCH void func_801EF070(void) {
    PartyBattler* work;

    if (func_8014D978() != 0u) {
        work              = g_Task;
        work->header.step = work->header.step + 1;
    } else {
        Area_AddActor();
    }
}

MATCH void func_801EF0C4(void) {
    func_801E5988();
}
