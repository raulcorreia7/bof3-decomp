#include "magic062_03.h"
#include "menu/clock.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_DispatchMode.h"

INCLUDE_ASM(func_801EEC94);

#include "overlays/bmagic/Effect_ReplacePaletteFade.h"

/* func_801EEF68 */
#include "overlays/bmagic/Effect_BrightenPalette.h"

/* func_801EF078 */
MATCH void Effect_NextStep(void) {
    BMagic_AdvanceEffectStep(2);
}

INCLUDE_ASM(func_801EF0C0);

MATCH void func_801EF2A0(void) {
    u16* flags;

    if (g_Task->param.unk_0B == 0) {
        flags                     = &g_Battle.state;
        g_GameCelerityTimer.hours = 5;
        *flags |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF2F0);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

/* func_801EF4C4 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF508(void) {
    SYS_DISPATCH_BYTE(D_801F0C18, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        func_801EF678();
        func_801EF934();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_StepWhileTickUnderThree.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801EF678);

INCLUDE_ASM(func_801EF934);

MATCH void func_801EFBBC(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 5), 2, g_Task);
}

#include "overlays/bmagic/Effect_CountDownAndStep.h"

INCLUDE_ASM(func_801EFC4C);

MATCH void func_801EFD80(void) {
    s32          timer;
    s32          vel;
    PartyMember* task;
    PartyMember* reset;

    Battle_ProjectRange();
    func_801F0910((RANDOM_MASK(3)) | 0x18);
    Effect_SetActorMatrix();
    func_801F026C();
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
    if ((timer & BYTE_MASK) == 0) {
        reset         = g_Task;
        reset->unk_14 = -0x10;
        reset->timer  = 8;
        reset->unk_20 = 4;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFE74(void) {
    s32          timer;
    s32          vel;
    PartyMember* task;

    Battle_ProjectRange();
    func_801F0910((RANDOM_MASK(3)) | 0x18);
    Effect_SetActorMatrix();
    func_801F026C();
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
    if ((timer & BYTE_MASK) == 0) {
        g_Task->timer = 28 - g_Task->param.unk_0B;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFF68(void) {
    s32 value;
    s32 value2;
    u8  value3;

    Battle_ProjectRange();
    if ((g_Task->unk_0C == 4) && (g_Task->timer < 5U)) {
        value2 = RANDOM_MASK(3) | 0x40;
    } else {
        value2 = RANDOM_MASK(3) | 0x18;
    }
    func_801F0910(value2);
    Effect_SetActorMatrix();
    func_801F026C();
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
        if (!(value3 & BYTE_MASK)) {
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

INCLUDE_ASM(func_801F00EC);

INCLUDE_ASM(func_801F026C);

INCLUDE_ASM(func_801F0910);
