#include "magic172_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EEDD8};

    SYS_DISPATCH_TASK(handlers, 1, g_Task);
}

INCLUDE_ASM(func_801EEC5C);

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

/* Aims the effect at the selected actor, projects its screen point as the effect's range, and advances once the
 * effect record's step is two. */
MATCH void func_801EF650(void) {
    PartyMember* actor;
    VECTOR       pos;

    if (g_Task->unk_09 < 0x10) {
        g_Task->unk_09 += 4;
    }
    actor  = g_Battle.selected_actor;
    pos.vx = (actor->pos.x.fixed >> 9) - 0x4000;
    pos.vy = (actor->pos.y.fixed >> 9) - 0x4000;
    pos.vz = (actor->pos.z.fixed + TO_COORD(256)) >> 17;
    func_800AF3A0(pos, 0x40);
    g_Task->unk_10 = g_Task->unk_0C;
    g_Task->unk_0C = ratan2(actor->pos.x.fixed - g_Task->pos.x.fixed, actor->pos.y.fixed - g_Task->pos.y.fixed);
    if (g_BattleEffects[g_Task->unk_04].header.step == 2) {
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_TickOnTimerNegative.h"

INCLUDE_ASM(func_801EF7CC);

INCLUDE_ASM(func_801EFA2C);

INCLUDE_ASM(func_801EFD04);

INCLUDE_ASM(func_801EFFE8);

INCLUDE_ASM(func_801F02C8);

INCLUDE_ASM(func_801F05E8);

INCLUDE_ASM(func_801F0908);
