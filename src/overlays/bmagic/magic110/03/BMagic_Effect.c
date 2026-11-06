#include "magic110_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_DispatchHandlerSlot1.h"

INCLUDE_ASM(func_801EEC94);

INCLUDE_ASM(func_801EEE68);

MATCH void func_801EEEDC(void) {
    u8 temp_v1;
    u8 temp_v1_2;

    func_801EF148();
    if (g_FrameCount & 1) {
        temp_v1 = g_Task->timer;
        if (temp_v1 < 0x10U) {
            g_Task->timer = temp_v1 + 2;
        }
        temp_v1_2      = g_Task->unk_09 + 1;
        g_Task->unk_09 = temp_v1_2;
        if ((temp_v1_2 & 0xFF) == 0x10) {
            g_Task->mode += 1;
        }
    }
}

/* blocker: counter clear schedule; first diff: lui a0,0x8014 (retail) against move s0,zero (candidate). */
INCLUDE_ASM(func_801EEF80);

MATCH void func_801EF068(void) {
    u8 temp_v0;
    u8 temp_v0_2;

    func_801EF148();
    if (!(g_FrameCount & 3)) {
        temp_v0 = g_Task->timer;
        if (temp_v0 != 0) {
            g_Task->timer = temp_v0 - 1;
        }
        temp_v0_2      = g_Task->unk_09 - 1;
        g_Task->unk_09 = temp_v0_2;
        if (!(temp_v0_2 & 0xFF)) {
            func_800A9820(g_BattleTargetSelector);
            g_Task->mode += 1;
        }
    }
}

#include "shared/Effect_StartPlaying.h"

INCLUDE_ASM(func_801EF148);

MATCH void func_801EF3F8(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

MATCH void func_801EF43C(void) {
    g_ScriptBank = 0x800C3800;
    SYS_DISPATCH_BYTE(D_801F0478, g_Task->step);
    if ((g_Task->flags & 1) && g_Task->step >= 2) {
        func_8014D290();
    }
    g_ScriptBank = 0x800D3800;
}

#include "overlays/bmagic/Effect_CountDownTimerStep.h"

/* blocker: work pointer lifetime; first diff: lui v1 at +0x20. */
INCLUDE_ASM(func_801EF528);

MATCH void func_801EF648(void) {
    PartyBattler* work;

    g_Task->unk_2E.half = (rand() & 3) + 0x9F;
    work                = g_Task;
    work->unk_30.half -= 2;
    work->scale.y += 0x2000;
    if (work->scale.y > 0x17FFF) {
        work->step++;
    }
}

MATCH void func_801EF6B4(void) {
    u16 temp_v1;

    g_Task->unk_2E.half = (rand() & 3) + 0x9F;
    temp_v1             = g_Task->unk_30.half - 4;
    g_Task->unk_30.half = temp_v1;
    if ((s16)temp_v1 < 0xB2) {
        D_801EB4E0->unk_0B -= 1;
        g_Task->step += 1;
    }
}

MATCH void func_801EF740(void) {
    u16 temp_v1;

    g_Task->unk_2E.half = (rand() & 3) + 0x9F;
    temp_v1             = g_Task->unk_30.half - 2;
    g_Task->unk_30.half = temp_v1;
    if ((s16)temp_v1 < 0x80) {
        D_801EB4E0->unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EF7B4(void) {
    SYS_DISPATCH_BYTE(D_801F048C, g_Task->step);
    if (g_Task->flags != 0 && g_Task->step != 0) {
        Effect_SetActorMatrix();
        func_801EFA48();
        func_801EFC98();
        PopMatrix();
    }
}

/* blocker: work pointer lifetime; first diff: lui v1 at entry. */
INCLUDE_ASM(func_801EF844);

MATCH void func_801EF8C0(void) {
    PartyBattler* work;

    work = g_Task;
    if ((work->unk_14 += 0x40) == 0xC00) {
        work->step++;
    }
}

#include "overlays/bmagic/Effect_StepWhileTickUnderThree.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EFA48);

INCLUDE_ASM(func_801EFC98);

MATCH void func_801EFFB8(void) {
    SYS_DISPATCH_BYTE(D_801F049C, g_Task->step);
    if (g_Task->flags != 0 && g_Task->step != 0) {
        func_801F0138();
        func_801F01E8();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801F0040);

MATCH void func_801F00D8(void) {
    PartyBattler* work;

    work         = g_Task;
    work->unk_09 = work->unk_09 + 2;
    work         = g_Task;
    work->timer  = work->timer - 1;
    if (work->timer == 0) {
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
