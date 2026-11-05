#include "magic110_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC1C(void) {
    BmagicEffectFuncs handlers = D_801EEC04;

    handlers.handlers[g_SpadWork->step_01]();
}

INCLUDE_ASM(func_801EEC94);

INCLUDE_ASM(func_801EEE68);

MATCH void func_801EEEDC(void) {
    u8 temp_v1;
    u8 temp_v1_2;

    func_801EF148();
    if (g_FrameCount & 1) {
        temp_v1 = g_SpadWork->word_08.byte.timer_0A;
        if (temp_v1 < 0x10U) {
            g_SpadWork->word_08.byte.timer_0A = temp_v1 + 2;
        }
        temp_v1_2                       = g_SpadWork->word_08.byte.unk_09 + 1;
        g_SpadWork->word_08.byte.unk_09 = temp_v1_2;
        if ((temp_v1_2 & 0xFF) == 0x10) {
            g_SpadWork->step_01 += 1;
        }
    }
}

/* Spawns six queued effects (Battle_AllocEffect(1, 0x10); unk_01 2, unk_0B the loop index, target the work record) after func_801EF148 when unk_0B is 0, then steps. Tried do-while and for loops, s8 and u8 counters and a work local: matches up to
 * the loop; first differing instruction lui a0,0x8014 retail against move s0,zero (retail schedules the counter clear after the selector load, before func_800A9610). */
INCLUDE_ASM(func_801EEF80);

MATCH void func_801EF068(void) {
    u8 temp_v0;
    u8 temp_v0_2;

    func_801EF148();
    if (!(g_FrameCount & 3)) {
        temp_v0 = g_SpadWork->word_08.byte.timer_0A;
        if (temp_v0 != 0) {
            g_SpadWork->word_08.byte.timer_0A = temp_v0 - 1;
        }
        temp_v0_2                       = g_SpadWork->word_08.byte.unk_09 - 1;
        g_SpadWork->word_08.byte.unk_09 = temp_v0_2;
        if (!(temp_v0_2 & 0xFF)) {
            func_800A9820(g_BattleTargetSelector);
            g_SpadWork->step_01 += 1;
        }
    }
}

#include "shared/Effect_StartPlaying.h"

INCLUDE_ASM(func_801EF148);

MATCH void func_801EF3F8(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
}

INCLUDE_ASM(func_801EF43C);

#include "overlays/bmagic/Effect_CountDownTimerStep.h"

INCLUDE_ASM(func_801EF528);

MATCH void func_801EF648(void) {
    PartyBattler* work;

    g_SpadWork->unk_2E.half = (rand() & 3) + 0x9F;
    work                    = g_SpadWork;
    work->unk_30.half -= 2;
    work->unk_44 += 0x2000;
    if (work->unk_44 > 0x17FFF) {
        work->unk_02++;
    }
}

MATCH void func_801EF6B4(void) {
    u16 temp_v1;

    g_SpadWork->unk_2E.half = (rand() & 3) + 0x9F;
    temp_v1                 = g_SpadWork->unk_30.half - 4;
    g_SpadWork->unk_30.half = temp_v1;
    if ((s16)temp_v1 < 0xB2) {
        D_801EB4E0->word_08.byte.unk_0B -= 1;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EF740(void) {
    u16 temp_v1;

    g_SpadWork->unk_2E.half = (rand() & 3) + 0x9F;
    temp_v1                 = g_SpadWork->unk_30.half - 2;
    g_SpadWork->unk_30.half = temp_v1;
    if ((s16)temp_v1 < 0x80) {
        D_801EB4E0->word_08.byte.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EF7B4(void) {
    SYS_DISPATCH_BYTE(D_801F048C, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801EFA48();
        func_801EFC98();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF844);

MATCH void func_801EF8C0(void) {
    PartyBattler* work;

    work = g_SpadWork;
    if ((work->unk_14 += 0x40) == 0xC00) {
        work->unk_02++;
    }
}

#include "overlays/bmagic/Effect_StepWhileTickUnderThree.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EFA48);

INCLUDE_ASM(func_801EFC98);

MATCH void func_801EFFB8(void) {
    SYS_DISPATCH_BYTE(D_801F049C, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801F0138();
        func_801F01E8();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801F0040);

MATCH void func_801F00D8(void) {
    PartyBattler* work;

    work                        = g_SpadWork;
    work->word_08.byte.unk_09   = work->word_08.byte.unk_09 + 2;
    work                        = g_SpadWork;
    work->word_08.byte.timer_0A = work->word_08.byte.timer_0A - 1;
    if (work->word_08.byte.timer_0A == 0) {
        func_801E5988();
    }
}

MATCH void Effect_SetActorMatrix_801F0138(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    BMAGIC_SET_ACTOR_MATRIX();
}

INCLUDE_ASM(func_801F01E8);
