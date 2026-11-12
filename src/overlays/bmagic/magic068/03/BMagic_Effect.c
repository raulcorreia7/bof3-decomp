#include "magic068_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC18.h"

MATCH void func_801EEC88(void) {
    u32          slot;
    PartyMember* task;

    g_Task->facing                     = g_BattleEffectBattler->facing;
    g_Task->pos.x.fixed                = g_BattleEffectBattler->pos.x.fixed;
    g_Task->pos.y.fixed                = g_BattleEffectBattler->pos.y.fixed;
    g_Task->pos.z.fixed                = g_BattleEffectBattler->pos.z.fixed;
    slot                               = Battle_AllocEffect(1, 28) & BYTE_MASK;
    task                               = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].target.party = task;
    g_Task->param.unk_0B               = 1;
    g_Task->header.mode += 1;
}

INCLUDE_ASM(func_801EED50);

MATCH void func_801EF44C(void) {
    u8 timer;

    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (timer == 0) {
        g_Task->timer       = 62;
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

MATCH void func_801EF4A8(void) {
    func_801EF55C();
    if (g_InputPressed != 0) {
        g_Task->header.mode = 4;
    }
}

MATCH void func_801EF4EC(void) {
    s8 val;

    if (D_801EC2E4 == 0) {
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
        return;
    }
    val = g_Task->unk_09;
    if (val > 0) {
        g_Task->unk_09 = val - 8;
        func_801EF55C();
    }
}

INCLUDE_ASM(func_801EF55C);

/* func_801EF73C */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF780(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectModes + 1, 2, g_Task);
}

MATCH void func_801EF7C4(void) {
    g_Task->facing      = g_BattleEffectBattler->facing;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
    g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + 0x02000000;
    Battle_ProjectRange();
    SND_QueueSelectionFx(0x100);
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0xF;
    g_Task->timer        = 3;
    g_Task->header.step += 1;
}

MATCH void func_801EF884(void) {
    u8 count;

    Effect_SetActorMatrix();
    func_801EFA48();
    PopMatrix();
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_Task->unk_09 = 0xF;
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EF908);

MATCH void func_801EF9D0(void) {
    u8 timer;

    Effect_SetActorMatrix();
    func_801EFA48();
    PopMatrix();
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        BMAGIC_TICK_EFFECT_WORK();
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EFA48);

#include "overlays/bmagic/Effect_SetActorMatrix.h"
