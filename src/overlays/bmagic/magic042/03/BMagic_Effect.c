#include "magic042_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC18(void) {
    BMagic_DispatchTaskPair(func_801EEC70, func_801EED44);
}

MATCH void func_801EEC70(void) {
    u32 slot;

    g_Task->facing       = g_BattleEffectBattler->facing;
    g_Task->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed;
    g_Task->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed;
    g_Task->pos.z.fixed  = g_BattleEffectBattler->pos.z.fixed;
    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 62) & BYTE_MASK;
    g_BattleEffects[slot].target.party = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_Task->param.unk_0B += 1;
    SND_QueueSelectionFx(0x100);
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEDA4 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEDE8(void) {
    Magic042Steps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Task);
    if (g_Task->header.flags & 0x1 && g_Task->header.step != 0) {
        func_801EF920();
        func_801EF380(0, g_Task->unk_09);
        func_801EF71C(g_Task->param.unk_0B + 8, g_Task->timer);
        func_801EF71C(g_Task->param.unk_0B + 0x10, g_Task->timer);
        func_801EF71C(g_Task->param.unk_0B + 0x18, g_Task->timer);
    }
}

MATCH void func_801EEF08(void) {
    g_Task->facing      = g_BattleEffectBattler->facing;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
    g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
    func_801EF1B0();
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0;
    g_Task->timer        = 0;
    g_Task->header.step += 1;
}

MATCH void func_801EEFB8(void) {
    PartyMember* work;

    work = g_Task;
    work->param.unk_0B++;
    work = g_Task;
    work->timer++;
    if (work->timer == 4) {
        work = g_Task;
        work->header.step++;
    }
}

MATCH void func_801EF024(void) {
    PartyMember* work;

    work = g_Task;
    work->param.unk_0B++;
    work = g_Task;
    work->unk_09 += 8;
    if (work->unk_09 == 80) {
        work = g_Task;
        work->header.step++;
    }
}

MATCH void func_801EF090(void) {
    u8 timer;

    g_Task->param.unk_0B += 1;
    g_Task->unk_09 += 4;
    timer         = g_Task->timer + 4;
    g_Task->timer = timer;
    if ((timer & BYTE_MASK) == 32) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF118(void) {
    u8 count;
    u8 timer_next;

    g_Task->param.unk_0B += 1;
    count = g_Task->unk_09;
    if (count != 0) {
        g_Task->unk_09 = count - 0xC;
    }
    timer_next    = g_Task->timer - 4;
    g_Task->timer = timer_next;
    if (!(timer_next & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF1B0);

INCLUDE_ASM(func_801EF380);

INCLUDE_ASM(func_801EF71C);

INCLUDE_ASM(func_801EF920);
