#include "magic086_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC1C.h"

INCLUDE_ASM(func_801EEC94);

MATCH void func_801EEE44(void) {
    PartyBattler* battler;

    battler = g_BattleSelectedActor;
    if (g_SpadWork->word_08.byte.unk_0B == 1) {
        func_80196718(battler);
        g_SpadWork->word_08.byte.timer_0A = func_8019651C(battler, 1, 1, 1, 0);
        g_SpadWork->word_08.byte.unk_09   = 0x10;
        g_SpadWork->step_01 += 1;
    }
}

INCLUDE_ASM(func_801EEEE0);

MATCH void func_801EEFF0(void) {
    PartyBattler* work;

    work = SP_REF(PartyBattler*, 0x44u);
    if (work->word_08.byte.unk_0B == 2) {
        work->step_01 = (u8)(work->step_01 + 1);
    }
}

INCLUDE_ASM(func_801EF024);

#include "overlays/bmagic/Effect_PlayOnIdleTick.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801EF278(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
}

MATCH void func_801EF2BC(void) {
    SYS_DISPATCH_BYTE(D_801F0360, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0) {
        Effect_SetActorMatrix();
        func_801EF424();
        PopMatrix();
    }
}

MATCH void func_801EF334(void) {
    g_SpadWork->word_08.byte.unk_09 += 1;
    g_SpadWork->word_08.byte.timer_0A += 1;
    if (g_SpadWork->word_08.byte.unk_09 == 0x10) {
        Bmagic_NextStep();
    }
}

MATCH void func_801EF3A0(void) {
    PartyBattler* active;
    PartyBattler* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->word_08.byte.unk_0B == 2) {
        work         = SP_REF(PartyBattler*, 0x44u);
        work->unk_02 = work->unk_02 + 1;
    }
}

MATCH void func_801EF3E0(void) {
    u8 timer;

    timer                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 0) {
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF424);

MATCH void func_801EF70C(void) {
    SYS_DISPATCH_BYTE(D_801F036C, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0) {
        Effect_SetActorMatrix();
        func_801EF9E0();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_CountUpAndStep.h"

/* Template: bmagic/magic040 func_801EF114; size 0x6C against retail 0x7C, first difference lbu v0,9(v1) at +0x0C. */
MATCH void func_801EF7D4(void) {
    u8 temp_v0;

    g_SpadWork->word_08.byte.timer_0A += 1;
    temp_v0                         = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if ((temp_v0 & 0xFF) == 0x18) {
        D_801EB4E0->word_08.byte.unk_0B = 1;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EF850(void) {
    u8 timer;

    timer                             = g_SpadWork->word_08.byte.timer_0A + 1;
    g_SpadWork->word_08.byte.timer_0A = timer;
    if (timer == 22) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

#include "overlays/bmagic/Effect_CountDownTickerAndStep.h"

MATCH void func_801EF8EC(void) {
    g_SpadWork->word_08.byte.unk_09 -= 1;
    g_SpadWork->word_08.byte.timer_0A -= 1;
    if (g_SpadWork->word_08.byte.unk_09 == 0x10) {
        D_801EB4E0->word_08.byte.unk_0B = 2;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EF974(void) {
    u8 temp_v0;
    u8 temp_v0_2;

    temp_v0 = g_SpadWork->word_08.byte.unk_09;
    if (temp_v0 != 0) {
        g_SpadWork->word_08.byte.unk_09 = temp_v0 - 1;
    }
    temp_v0_2                         = g_SpadWork->word_08.byte.timer_0A - 1;
    g_SpadWork->word_08.byte.timer_0A = temp_v0_2;
    if (!(temp_v0_2 & 0xFF)) {
        D_801EB4E0->word_08.byte.unk_0B = 0xFF;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF9E0);

MATCH void func_801F0038(void) {
    SYS_DISPATCH_BYTE(D_801F0384, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801F01A8();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_NextStepOnLastTick.h"

MATCH void func_801F0100(void) {
    u8 temp_v0;

    temp_v0                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_SpadWork->unk_14 = 0x20;
        g_SpadWork->unk_20 = -1;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801F0154(void) {
    s32 temp_a1;

    temp_a1                          = g_SpadWork->unk_14 + g_SpadWork->unk_20;
    g_SpadWork->unk_14               = temp_a1;
    g_SpadWork->word_3C.half.span_3E = (u16)g_SpadWork->word_3C.half.span_3E + temp_a1;
    if (g_SpadWork->unk_14 < -0x10) {
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F01A8);
