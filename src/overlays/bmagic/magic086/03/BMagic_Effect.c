#include "magic086_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_DispatchMode.h"

INCLUDE_ASM(func_801EEC94);

MATCH void func_801EEE44(void) {
    PartyMember* battler;

    battler = g_BattleSelectedActor;
    if (g_Task->param.unk_0B == 1) {
        GFX_FreePaletteFadeTarget(battler);
        g_Task->timer  = GFX_AllocPaletteFade(battler, 1, 1, 1, 0);
        g_Task->unk_09 = 0x10;
        g_Task->header.mode += 1;
    }
}

#include "overlays/bmagic/Effect_BrightenPalette.h"

MATCH void func_801EEFF0(void) {
    PartyMember* work;

    work = g_Task;
    if (work->param.unk_0B == 2) {
        work->header.mode = (work->header.mode + 1);
    }
}

INCLUDE_ASM(func_801EF024);

#include "overlays/bmagic/Effect_PlayOnIdleTick.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801EF278(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

MATCH void func_801EF2BC(void) {
    SYS_DISPATCH_BYTE(D_801F0360, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        func_801EF424();
        PopMatrix();
    }
}

MATCH void func_801EF334(void) {
    g_Task->unk_09 += 1;
    g_Task->timer += 1;
    if (g_Task->unk_09 == 0x10) {
        BMagic_NextStep();
    }
}

MATCH void func_801EF3A0(void) {
    PartyMember* active;
    PartyMember* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->param.unk_0B == 2) {
        work              = g_Task;
        work->header.step = work->header.step + 1;
    }
}

MATCH void func_801EF3E0(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF424);

MATCH void func_801EF70C(void) {
    SYS_DISPATCH_BYTE(D_801F036C, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        func_801EF9E0();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_CountUpAndStep.h"

/* Template: bmagic/magic040 func_801EF114; size 0x6C against retail 0x7C, first difference lbu v0,9(v1) at +0x0C. */
MATCH void func_801EF7D4(void) {
    u8 count;

    g_Task->timer += 1;
    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x18) {
        g_BattleEffectBattler->param.unk_0B = 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF850(void) {
    u8 timer;

    timer         = g_Task->timer + 1;
    g_Task->timer = timer;
    if (timer == 22) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

#include "overlays/bmagic/Effect_CountDownTickerAndStep.h"

MATCH void func_801EF8EC(void) {
    g_Task->unk_09 -= 1;
    g_Task->timer -= 1;
    if (g_Task->unk_09 == 0x10) {
        g_BattleEffectBattler->param.unk_0B = 2;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF974(void) {
    u8 count;
    u8 timer_next;

    count = g_Task->unk_09;
    if (count != 0) {
        g_Task->unk_09 = count - 1;
    }
    timer_next    = g_Task->timer - 1;
    g_Task->timer = timer_next;
    if (!(timer_next & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B = 0xFF;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF9E0);

MATCH void func_801F0038(void) {
    SYS_DISPATCH_BYTE(D_801F0384, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801F01A8();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_NextStepOnLastTick.h"

MATCH void func_801F0100(void) {
    u8 temp_v0;

    temp_v0        = g_Task->unk_09 - 1;
    g_Task->unk_09 = temp_v0;
    if (!(temp_v0 & BYTE_MASK)) {
        g_Task->unk_14 = 0x20;
        g_Task->unk_20 = -1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F0154(void) {
    s32 temp_a1;

    temp_a1                  = g_Task->unk_14 + g_Task->unk_20;
    g_Task->unk_14           = temp_a1;
    COORD_INT(g_Task->pos.z) = COORD_INT(g_Task->pos.z) + temp_a1;
    if (g_Task->unk_14 < -0x10) {
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F01A8);
