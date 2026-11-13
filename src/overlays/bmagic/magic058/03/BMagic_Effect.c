#include "magic058_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC28(void) {
    Magic058Steps handlers = D_801EEC04;
    PartyMember*  saved_task;
    PartyMember*  saved_battler;
    u8            i;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.mode);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (BMAGIC_EFFECT_SLOTS[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&BMAGIC_EFFECT_SLOTS[i];
            g_BattleEffectBattler = BMAGIC_EFFECT_SLOTS[i].target.party;
            func_801EF36C();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

INCLUDE_ASM(func_801EED30);

MATCH void func_801EEE78(void) {
    if (g_Task->param.unk_0B == 0) {
        func_801DE8C0(1, 0x3C, Message_GetText(0x14U));
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEEDC(void) {
    if (D_801EC2E4 == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}

/* func_801EEF30 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF74(void) {
    Magic058Steps handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        func_801EF74C();
        PopMatrix();
    }
}

MATCH void func_801EF008(void) {
    PartyMember* work;
    PartyMember* actor;
    s32          z;

    g_Task->facing    = g_BattleEffectBattler->facing;
    work              = g_Task;
    actor             = g_BattleEffectBattler;
    work->pos.x.fixed = actor->pos.x.fixed;
    work->pos.y.fixed = actor->pos.y.fixed;
    z                 = actor->pos.z.fixed;
    work->timer       = 16;
    work->unk_0C      = 8;
    work->pos.z.fixed = z;
    g_Task->header.step += 1;
}

INCLUDE_ASM(func_801EF080);

#include "overlays/bmagic/Effect_TickDownAndClear.h"

MATCH void func_801EF36C(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 1), 1, g_Task);
}

MATCH void func_801EF3B0(void) {
    Magic058Steps handlers;

    handlers = D_801EEC1C;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EFA78();
        PopMatrix();
    }
}

MATCH void func_801EF454(void) {
    PartyMember* work;
    u8           count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        work = g_Task;
        /* kept: retail reloads the battler row at each access; a PartyMember* local changes the bytes. */
        if (BATTLER_IS_PLAYER(work->param.unk_0B)) {
            work->pos.x.fixed = g_Game.members[work->param.unk_0B].pos.x.fixed;
            work->pos.y.fixed = g_Game.members[work->param.unk_0B].pos.y.fixed;
            work->pos.z.fixed = g_Game.members[work->param.unk_0B].pos.z.fixed;
        } else {
            work->pos.x.fixed = ENEMY_COMBATANT(work->param.unk_0B).pos.x.fixed;
            work->pos.y.fixed = ENEMY_COMBATANT(work->param.unk_0B).pos.y.fixed;
            work->pos.z.fixed = ENEMY_COMBATANT(work->param.unk_0B).pos.z.fixed;
        }
        g_Task->unk_0C = 16;
        g_Task->unk_18 = 16;
        g_Task->timer  = 16;
        g_Task->header.step += 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF5D4(void) {
    PartyMember* work;

    work         = g_Task;
    work->unk_0C = work->unk_0C + work->unk_18;
    if (--work->unk_18 == 0x10) {
        work->header.step++;
    }
}

INCLUDE_ASM(func_801EF61C);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF74C);

INCLUDE_ASM(func_801EFA78);

INCLUDE_ASM(func_801EFDD4);

/* func_801EFE38 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801EFE9C */
#include "overlays/bmagic/Actor_Clear.h"
