#include "magic006_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC38(void) {
    BMagic_DispatchTaskPair(func_801EEC90, func_801EEDA4);
}

INCLUDE_ASM(func_801EEC90);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEE04(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

MATCH void func_801EEE48(void) {
    BMagicEffectFuncs handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_800AF764();
        if (g_Task->param.unk_0B != 0) {
            func_801EFB6C();
        } else {
            func_801EF478();
        }
    }
}

MATCH void func_801EEF28(void) {
    PartyBattler* battler;
    u8            value;

    value          = g_Task->unk_09 - 1;
    g_Task->unk_09 = value;
    if (!(value & 0xFF)) {
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + TO_COORD(128);
        func_800AF764();
        battler        = g_BattleSelectedActor;
        g_Task->unk_0C = ratan2(battler->pos.x.fixed - g_Task->pos.x.fixed, battler->pos.y.fixed - g_Task->pos.y.fixed);
        g_Task->unk_10 = 0;
        g_Task->unk_14 = (ratan2((s16)battler->unk_2E.half - (s16)g_Task->unk_2E.half,
                                 (s16)battler->unk_30.half - (s16)g_Task->unk_30.half) -
                          0x200) &
                         0xFFF;
        SND_QueueSelectionFx(0x100);
        g_Task->unk_09 = 0x20;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF04C(void) {
    PartyBattler* work = g_Task;
    u8            timer;

    work->unk_14 += 0x80;

    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    if (timer == 0) {
        g_Task->unk_09 = g_Task->param.unk_0B + 0xC;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF0B8(void) {
    PartyBattler* work;

    work         = g_Task;
    work->unk_09 = work->unk_09 - 1;
    if (work->unk_09 == 0) {
        SND_QueueSelectionFx(0x101);
        g_Task->header.step = g_Task->header.step + 1;
    }
}

INCLUDE_ASM(func_801EF118);

INCLUDE_ASM(func_801EF298);

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801EF478);

INCLUDE_ASM(func_801EFB6C);

MATCH void func_801F0064(void) {
    Magic006Steps handlers;

    handlers = D_801EEC1C;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_800AF764();
        func_801F0308();
    }
}

MATCH void func_801F0100(void) {
    PartyBattler* actor;
    PartyBattler* work;
    s16*          angle_cell;
    u8            count;
    u8            phase;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        phase                        = g_Task->param.unk_0B;
        angle_cell                   = &D_1F800008;
        *angle_cell                  = phase << 9;
        actor                        = g_BattleSelectedActor;
        g_Task->pos.x.fixed          = actor->pos.x.fixed + ((rcos((s16)(phase << 9)) * 0xC000) >> 12);
        (work = g_Task)->pos.y.fixed = actor->pos.y.fixed + ((rsin(*angle_cell) * 0xC000) >> 12);
        work->pos.z.fixed            = actor->pos.z.fixed;
        work->unk_09                 = 0;
        g_Task->timer                = 4;
        g_Task->header.step++;
    }
}

MATCH void func_801F020C(void) {
    u8 counter;

    if (g_FrameCount & 1) {
        g_Task->timer += 1;
    }
    counter        = g_Task->unk_09 + 0x10;
    g_Task->unk_09 = counter;
    if ((counter & 0xFF) == 0x80) {
        g_Task->header.step += 1;
    }
}

/* func_801F0290 */
MATCH void Effect_CountDownTimer(void) {
    BMagic_CountDownEffectTimer(8);
}

INCLUDE_ASM(func_801F0308);

MATCH void func_801F04F4(void) {
    Magic006SecondSteps handlers;

    handlers = D_801EEC28;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801F0790();
        PopMatrix();
    }
}

MATCH void func_801F05A4(void) {
    PartyBattler* src;

    src                 = g_BattleSelectedActor;
    g_Task->pos.x.fixed = src->pos.x.fixed;
    g_Task->pos.y.fixed = src->pos.y.fixed;
    g_Task->pos.z       = src->pos.z;
    g_Task->unk_09      = 0;
    g_Task->header.step = g_Task->header.step + 1;
}

MATCH void func_801F05F4(void) {
    u8 timer;

    timer          = g_Task->unk_09 + 4;
    g_Task->unk_09 = timer;
    if (timer == 16) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

#include "overlays/bmagic/Effect_NextStepOnLastTick.h"

MATCH void Effect_TickOnTimerZero_801F0684(void) {
    PartyBattler* work;

    BMAGIC_TICK_ON_TIMER_ZERO(EFFECT_TIMER_TICK);
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801F0790);
