#include "magic081_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(SAVE_AccessFile);

INCLUDE_ASM(func_801EED44);

MATCH void func_801EEE74(void) {
    PartyMember* saved;

    saved  = g_Task;
    g_Task = D_801EC2E0->target.party;
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        saved->header.mode++;
    }
    g_Task = saved;
}

INCLUDE_ASM(func_801EEEDC);

MATCH void func_801EEF88(void) {
    PartyMember* saved_work;

    saved_work = g_Task;
    g_Task     = D_801EC2E0->target.party;
    Actor_StepAnimOnce();
    g_Task = saved_work;
    if (saved_work->param.unk_0B == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}

/* func_801EF014 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF058(void) {
    Magic081Steps handlers;

    handlers = D_801EEC14;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Task);
}

MATCH void func_801EF0B8(void) {
    u32          slot;
    u8           effect_index;
    PartyMember* task;

    g_Task->pos.x.fixed                        = g_BattleEffectBattler->pos.x.fixed + TO_COORD(2);
    g_Task->pos.y.fixed                        = g_BattleEffectBattler->pos.y.fixed;
    COORD_INT(g_Task->pos.z)                   = COORD_INT(g_BattleEffectBattler->pos.z);
    slot                                       = Battle_AllocEffect(1, 66);
    effect_index                               = slot & BYTE_MASK;
    task                                       = g_Task;
    g_BattleEffects[effect_index].header.mode  = 1;
    g_BattleEffects[effect_index].target.party = task;
    g_Task->timer                              = slot;
    SND_QueueSelectionFx(0x100);
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0;
    g_Task->header.step += 1;
}

INCLUDE_ASM(func_801EF18C);

#include "overlays/bmagic/Effect_TickOnZeroTick.h"

MATCH void func_801EF2F0(void) {
    if (g_Battle.state & BATTLE_STATE_EFFECT_PLAYING) {
        func_801E5988();
    } else {
        Battle_CenterCamera();
    }
}

MATCH void func_801EF330(void) {
    Magic081SecondSteps handlers;

    handlers = D_801EEC20;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Task);
}

MATCH void func_801EF39C(void) {
    u8 effect_slot;

    g_Task->pos.x.fixed      = g_BattleEffectBattler->pos.x.fixed + TO_COORD(1) / 8;
    g_Task->pos.y.fixed      = g_BattleEffectBattler->pos.y.fixed;
    COORD_INT(g_Task->pos.z) = COORD_INT(g_BattleEffectBattler->pos.z) + 256;
    effect_slot              = g_BattleEffectBattler->timer;
    g_Task->unk_14           = ratan2(g_BattleEffects[effect_slot].pos.x.fixed - g_Task->pos.x.fixed, g_BattleEffects[effect_slot].pos.y.fixed - g_Task->pos.y.fixed);
    g_Task->unk_09           = 0;
    g_Task->header.step += 1;
}

MATCH void func_801EF44C(void) {
    s32 angle;
    s32 phase;
    u8  count;

    phase          = (g_Task->unk_09 + g_Task->param.unk_0B) & 0x3F;
    SP_REF(s16, 2) = BMAGIC_PHASE_ANGLE(phase);
    angle          = g_Task->unk_14 + ((rsin((s16)BMAGIC_PHASE_ANGLE(phase)) * 0x12C) >> 0xC);
    g_Task->unk_0C = angle;
    g_Task->pos.x.fixed += (rsin(angle) * 0x7000) >> 0xC;
    g_Task->pos.y.fixed += (rcos(g_Task->unk_0C) * 0x7000) >> 0xC;
    Battle_ProjectRange();
    func_801EF6A0();
    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x10) {
        g_Task->timer = 64;
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EF57C);

MATCH void func_801EF614(void) {
    Battle_ProjectRange();
    func_801EF6A0();
    BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
    g_Task->header.flags = 0;
    g_Task->header.mode  = 0;
    g_Task->header.step  = 0;
    g_Task->unk_03       = 0;
    g_Task->unk_04       = 0;
}

INCLUDE_ASM(func_801EF6A0);

/* func_801EFA20 */
#include "overlays/bmagic/BMagic_AllocEffect.h"
