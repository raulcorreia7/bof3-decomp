#include "magic104_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC14.h"

INCLUDE_ASM(func_801EEC80);

MATCH void func_801EEE7C(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 7) {
        g_SpadWork->word_08.byte.unk_09 = 8;
        g_SpadWork->step_01 += 1;
    }
}

INCLUDE_ASM(func_801EEEC0);

MATCH void func_801EF03C(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 7) {
        func_800A9820(g_BattleTargetSelector);
        g_BattleState |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}

MATCH void func_801EF09C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
}

MATCH void func_801EF0E0(void) {
    SYS_DISPATCH_BYTE(D_801F08F0, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801EFA54();
        func_801EFE34();
        func_801EFB2C();
        func_801EF370();
        PopMatrix();
    }
}

MATCH void func_801EF178(void) {
    s32 var_a0;
    u8  temp_v0;

    temp_v0                           = g_SpadWork->word_08.byte.timer_0A - 1;
    g_SpadWork->word_08.byte.timer_0A = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        var_a0 = 0x100;
        if (g_SpadWork->word_08.byte.unk_0B & 1) {
            var_a0 = 0x101;
        }
        SND_QueueSelectionFx(var_a0);
        g_SpadWork->word_08.byte.unk_09   = 0;
        g_SpadWork->word_08.byte.timer_0A = 0;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EF21C(void) {
    u8 temp_v1;

    temp_v1                         = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v1;
    if ((temp_v1 & 0xFF) == 8) {
        g_SpadWork->word_08.byte.timer_0A = 0;
        g_SpadWork->unk_02 += 1;
    }
}

/* Template: bmagic/magic040 func_801EF114; size 0x6C against retail 0x7C, first difference lbu v0,9(v1) at +0x0C. */
MATCH void func_801EF27C(void) {
    u8 temp_v0;

    g_SpadWork->word_08.byte.timer_0A += 1;
    temp_v0                         = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if ((temp_v0 & 0xFF) == 0x10) {
        g_SpadWork->word_08.byte.timer_0A = 0;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EF2F8(void) {
    PartyBattler* work;
    PartyBattler* active;

    work                        = g_SpadWork;
    work->word_08.byte.timer_0A = work->word_08.byte.timer_0A + 1;
    work                        = g_SpadWork;
    work->word_08.byte.unk_09   = work->word_08.byte.unk_09 + 1;
    if (work->word_08.byte.unk_09 == 0x18) {
        active                      = BATTLE_ACTIVE_WORK;
        active->word_08.byte.unk_0B = g_SpadWork->word_08.byte.unk_0B;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF370);

INCLUDE_ASM(func_801EFA54);

INCLUDE_ASM(func_801EFB2C);

INCLUDE_ASM(func_801EFE34);

INCLUDE_ASM(func_801F020C);

INCLUDE_ASM(func_801F02F4);

INCLUDE_ASM(func_801F034C);

INCLUDE_ASM(func_801F03C4);
