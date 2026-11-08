#include "magic082_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_DispatchMode.h"

INCLUDE_ASM(func_801EEC94);

#include "overlays/bmagic/Effect_ReplacePaletteFade.h"

#include "overlays/bmagic/Effect_BrightenPalette.h"

#include "overlays/bmagic/Effect_NextStep.h"

INCLUDE_ASM(func_801EF10C);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

INCLUDE_ASM(func_801EF3A0);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801EF56C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

MATCH void func_801EF5B0(void) {
    SYS_DISPATCH_BYTE(D_801F0D1C, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        func_801EFA00();
        func_801EF720();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_StepWhileTickUnderThree.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801EF720);

INCLUDE_ASM(func_801EFA00);

MATCH void func_801EFD30(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 5), 2, g_Task);
}

#include "overlays/bmagic/Effect_CountDownAndStep.h"

/* blocker: y offset order; first diff: +0x94 sll v1,v0,1 (retail finishes the rcos*0xB0>>3 product before loading g_BattleEffectBattler for y and z, cached in a1) against the battler load first (candidate); body is the angle-ring start of magic213 with radius 0xB0 >> 3. */
INCLUDE_ASM(func_801EFDC0);

MATCH void func_801EFEF4(void) {
    s32           timer;
    s32           vel;
    PartyBattler* task;
    PartyBattler* reset;

    func_800AF764();
    func_801F0A84((rand() & 3) | 0x18);
    Effect_SetActorMatrix();
    func_801F03E0();
    PopMatrix();
    if (g_FrameCount & 1) {
        g_Task->unk_09 += 1;
    }
    task         = g_Task;
    timer        = task->timer - 1;
    vel          = task->unk_14 + task->unk_20;
    task->timer  = timer;
    task->unk_14 = vel;
    task->pos.z.part.integer += vel;
    if ((timer & 0xFF) == 0) {
        reset         = g_Task;
        reset->unk_14 = -0x10;
        reset->timer  = 8;
        reset->unk_20 = 4;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFFE8(void) {
    s32           timer;
    s32           vel;
    PartyBattler* task;

    func_800AF764();
    func_801F0A84((rand() & 3) | 0x18);
    Effect_SetActorMatrix();
    func_801F03E0();
    PopMatrix();
    if (g_FrameCount & 1) {
        g_Task->unk_09 += 1;
    }
    task         = g_Task;
    timer        = task->timer - 1;
    vel          = task->unk_14 + task->unk_20;
    task->timer  = timer;
    task->unk_14 = vel;
    task->pos.z.part.integer += vel;
    if ((timer & 0xFF) == 0) {
        g_Task->timer = 0x1C - g_Task->param.unk_0B;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F00DC(void) {
    s32 value;
    s32 value2;
    u8  value3;

    func_800AF764();
    if ((g_Task->unk_0C == 4) && (g_Task->timer < 5U)) {
        value2 = RANDOM_MASK(3) | 0x40;
    } else {
        value2 = RANDOM_MASK(3) | 0x18;
    }
    func_801F0A84(value2);
    Effect_SetActorMatrix();
    func_801F03E0();
    PopMatrix();
    if (g_Task->unk_0C < 4) {
        value          = g_Task->unk_10 + 1;
        g_Task->unk_10 = value;
        if (!(value & 7)) {
            g_Task->unk_0C += 1;
        }
    }
    g_Task->unk_09 += g_Task->unk_0C;
    if (g_Task->unk_0C == 4) {
        value3        = g_Task->timer - 1;
        g_Task->timer = value3;
        if (!(value3 & 0xFF)) {
            if (g_Task->param.unk_0B == 0) {
                SND_QueueSelectionFx(0x101);
            }
            g_Task->unk_10 = 8;
            g_Task->unk_14 = 8;
            g_Task->unk_20 = 8;
            g_Task->header.step += 1;
        }
    }
}

/* hint: 3-image twin (magic062 00EC, 082 0260, 083 038C): spiral position update; everything matches except the s16 radius cell at 0x1F800000: retail uses a separate lui per access, a cast view of D_1F800000 hoists the base into s1 (needs an s16 alias symbol for 0x1F800000, scratch draft b26-magic062.c) */
INCLUDE_ASM(func_801F0260);

INCLUDE_ASM(func_801F03E0);

INCLUDE_ASM(func_801F0A84);
