#include "magic125_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    PartyMember* saved_task;
    PartyMember* saved_battler;
    u8           i;

    BMagic_DispatchTaskPair(func_801EED04, Effect_PlayOnZeroTick);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (BMAGIC_EFFECT_SLOTS[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&BMAGIC_EFFECT_SLOTS[i];
            g_BattleEffectBattler = BMAGIC_EFFECT_SLOTS[i].target.party;
            func_801EFB48();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

INCLUDE_ASM(func_801EED04);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEEC0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF04(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 2), 2, g_Task);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        if ((g_FrameCount & 0x1) == 0) {
            g_Task->unk_5D = (RANDOM_MASK(3)) + 4;
            g_Task->unk_5E = (RANDOM_MASK(3)) + 4;
            g_Task->unk_5F = (RANDOM_MASK(3)) + 4;
        }
        Effect_SetActorMatrix();
        func_801EF258();
        func_801EF508();
        PopMatrix();
    }
}

MATCH void func_801EEFF8(void) {
    u8 count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + 0x04000000;
        g_Task->unk_5D      = (RANDOM_MASK(3)) + 4;
        g_Task->unk_5E      = (RANDOM_MASK(3)) + 4;
        g_Task->unk_5F      = (RANDOM_MASK(3)) + 4;
        g_Task->unk_14      = 0x100;
        g_Task->unk_09      = 0x10;
        g_Task->timer       = 8;
        g_Task->header.step += 1;
    }
}

/* func_801EF0F8 */
MATCH void Effect_Rise(void) {
    PartyMember* work  = g_Task;
    u8           timer = work->timer - 1;
    work->timer        = timer;
    work->pos.z.fixed += TO_COORD(-128);
    if (timer == 0) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF148(void) {
    PartyMember* work = g_Task;
    u8           timer;

    work->unk_14 += 0x20;

    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    if (timer == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF258);

INCLUDE_ASM(func_801EF508);

MATCH void func_801EF808(void) {
    SYS_DISPATCH_BYTE(D_801F05EC, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EF508();
        PopMatrix();
    }
}

MATCH void func_801EF890(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
        g_Task->unk_5D      = 0xF;
        g_Task->unk_5E      = 0xF;
        g_Task->unk_5F      = 0xF;
        g_Task->unk_14      = 0x100;
        g_Task->unk_20      = 0x21;
        g_Task->unk_09      = 0x10;
        g_Task->timer       = 30;
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EF960);

MATCH void func_801EFAB0(void) {
    s32 level;
    u8  counter;

    level = g_Task->unk_14;
    if (level >= 9) {
        g_Task->unk_14 = level - 1;
    }
    if (g_FrameCount & 0x1) {
        counter        = g_Task->unk_09 - 1;
        g_Task->unk_09 = counter;
        if (!(counter & BYTE_MASK)) {
            BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
            func_801E5988();
        }
    }
}

MATCH void func_801EFB48(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 8), 1, g_Task);
}

INCLUDE_ASM(func_801EFB8C);

INCLUDE_ASM(func_801EFCE4);

INCLUDE_ASM(func_801EFE8C);

INCLUDE_ASM(func_801EFFC8);

INCLUDE_ASM(func_801F020C);

/* func_801F0524 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0588 */
#include "overlays/bmagic/Actor_Clear.h"
