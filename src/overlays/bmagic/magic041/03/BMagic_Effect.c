#include "magic041_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_DispatchHandlerSlot1.h"

INCLUDE_ASM(func_801EECB0);

MATCH void func_801EEE14(void) {
    u8             temp_v0;
    PartyBattler** selected;

    temp_v0        = g_Task->unk_09 - 1;
    g_Task->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        selected = &g_BattleSelectedActor;
        func_80196718(*selected);
        g_Task->unk_09 = func_8019651C(*selected, 0, 0, 0, 1);
        g_Task->mode += 1;
    }
}

INCLUDE_ASM(func_801EEEB4);

#include "overlays/bmagic/Effect_NextStepOnWorkLastTick.h"

INCLUDE_ASM(func_801EEFF8);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EF190(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

MATCH void func_801EF1D4(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC1C;
    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->step);
    if (ACTOR_IN_USE(*g_Task) && g_Task->step != 0) {
        Effect_SetActorMatrix();
        func_801EF670();
        PopMatrix();
    }
}

MATCH void func_801EF27C(void) {
    PartyBattler* src;
    PartyBattler* dst;

    if (--g_Task->unk_09 == 0) {
        src            = D_801EB4E0;
        dst            = g_Task;
        dst->pos.x.raw = src->pos.x.raw;
        dst->pos.y.raw = src->pos.y.raw;
        dst->pos.z     = src->pos.z;
        dst->unk_09    = 0;
        g_Task->timer  = 0;
        g_Task->step++;
    }
}

MATCH void func_801EF308(void) {
    u8 timer;

    timer         = g_Task->timer + 4;
    g_Task->timer = timer;
    if (timer == 32) {
        g_Task->step = g_Task->step + 1;
    }
}

MATCH void func_801EF358(void) {
    PartyBattler* work;
    PartyBattler* active;
    u8            count;

    work = g_Task;
    work->unk_09 += 4;
    work        = g_Task;
    count       = work->timer - 1;
    work->timer = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->unk_0B--;
        func_801E5988();
    }
}

MATCH void func_801EF3D0(void) {
    MagicTaskFuncs handlers;

    handlers = D_801EEC28;
    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->step);
    if (ACTOR_IN_USE(*g_Task) && g_Task->step != 0) {
        Effect_SetActorMatrix();
        func_801EFAB8();
        PopMatrix();
    }
}

MATCH void func_801EF484(void) {
    PartyBattler* src;

    src               = (PartyBattler*)D_801EB4E0;
    g_Task->pos.x.raw = src->pos.x.raw;
    g_Task->pos.y.raw = src->pos.y.raw;
    g_Task->pos.z     = src->pos.z;
    g_Task->unk_09    = 0;
    g_Task->step      = g_Task->step + 1;
}

#include "overlays/bmagic/Effect_CountUpByTwoAndStep.h"

#include "overlays/bmagic/Effect_NextStepOnLastTick.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF670);

INCLUDE_ASM(func_801EFAB8);
