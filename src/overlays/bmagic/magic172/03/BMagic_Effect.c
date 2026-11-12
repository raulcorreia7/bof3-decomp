#include "magic172_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EEDD8};

    SYS_DISPATCH_TASK(handlers, 1, g_Task);
}

MATCH void func_801EEC5C(void) {
    PartyMember* work;
    PartyMember* target;
    u8           slot;
    u32          first_slot;
    u32          i;

    g_Task->facing       = g_BattleEffectBattler->facing;
    g_Task->pos.x        = g_BattleEffectBattler->pos.x;
    g_Task->pos.y        = g_BattleEffectBattler->pos.y;
    g_Task->pos.z        = g_BattleEffectBattler->pos.z;
    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    first_slot                               = Battle_AllocEffect(1, 0x51) & BYTE_MASK;
    work                                     = g_Task;
    g_BattleEffects[first_slot].header.mode  = 0;
    g_BattleEffects[first_slot].target.party = work;
    g_Task->param.unk_0B += 1;
    i = 0;
    do {
        slot                               = Battle_AllocEffect(1, 0x51);
        target                             = g_Task;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].unk_04       = first_slot;
        g_BattleEffects[slot].arg.unk_09   = i + 1;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].target.party = target;
        g_Task->param.unk_0B += 1;
        i++;
    } while (i < 8);
    SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0));
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEE38 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

INCLUDE_ASM(func_801EEE7C);

INCLUDE_ASM(func_801EF158);

INCLUDE_ASM(func_801EF210);

MATCH void func_801EF3A4(void) {
    u8 counter;
    u8 timer;

    g_Task->param.unk_0B += 2;
    timer = g_Task->timer;
    if (timer < 16U) {
        g_Task->timer = timer + 2;
    }
    counter        = g_Task->unk_09 - 1;
    g_Task->unk_09 = counter;
    if (!(counter & BYTE_MASK)) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF430(void) {
    u8 timer_next;

    g_Task->param.unk_0B += 4;
    timer_next    = g_Task->timer - 2;
    g_Task->timer = timer_next;
    if (!(timer_next & BYTE_MASK)) {
        SND_QueueSelectionFx(0x102);
        g_Task->unk_09 = 0x10;
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

MATCH void func_801EF518(void) {
    D_801F0B90[g_Task->header.step]();
    if (g_Task->header.flags & g_Task->header.step) {
        Battle_ProjectRange();
        func_801F0908();
    }
}

INCLUDE_ASM(func_801EF590);

INCLUDE_ASM(func_801EF650);

#include "overlays/bmagic/Effect_TickOnTimerNegative.h"

INCLUDE_ASM(func_801EF7CC);

INCLUDE_ASM(func_801EFA2C);

INCLUDE_ASM(func_801EFD04);

INCLUDE_ASM(func_801EFFE8);

INCLUDE_ASM(func_801F02C8);

INCLUDE_ASM(func_801F05E8);

INCLUDE_ASM(func_801F0908);
