#include "magic052_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

MATCH void func_801EEC7C(void) {
    PartyBattler* work;

    g_SpadWork->word_08.byte.unk_09   = 8;
    g_SpadWork->word_08.byte.timer_0A = 4;
    work                              = g_SpadWork;
    work->step_01                     = work->step_01 + 1;
}

INCLUDE_ASM(func_801EECBC);

MATCH void func_801EEE30(void) {
    if (g_SpadWork->word_08.byte.timer_0A-- == 0) {
        func_800A9820(g_BattleTargetSelector);
        g_BattleState |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}

MATCH void func_801EEE94(void) {
    Callback handlers[2];

    handlers[0] = func_801EEEE0;
    handlers[((u8*)g_SpadWork)[1]]();
}

INCLUDE_ASM(func_801EEEE0);

MATCH void func_801EEF84(void) {
    PartyBattler* work;
    s32           var_a0;
    u8            temp_v0;

    g_SpadWork->unk_29 = 0;
    g_SpadWork->unk_25 = 0x1D;
    g_SpadWork->unk_26 = 0;
    g_SpadWork->unk_24 = 0x84;
    g_SpadWork->unk_27 = 0xB4;
    g_SpadWork->unk_28 = 0;
    work               = g_SpadWork;
    work->unk_2B       = 0;
    work->unk_2C.half  = 0;
    g_SpadWork->unk_2A = 0;
    temp_v0            = g_SpadWork->word_08.byte.unk_09;
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
    g_SpadWork->unk_02 += 1;
}

MATCH void func_801EF070(void) {
    PartyBattler* work;

    if (func_8014D978() != 0u) {
        work         = g_SpadWork;
        work->unk_02 = work->unk_02 + 1;
    } else {
        Area_AddActor();
    }
}

MATCH void func_801EF0C4(void) {
    func_801E5988();
}
