#include "magic129_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC10(void) {
    Magic129Steps handlers = D_801EEC04;
    PartyMember*  saved_task;
    PartyMember*  saved_battler;
    u8            i;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.mode);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (D_801F05D8[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&D_801F05D8[i];
            g_BattleEffectBattler = D_801F05D8[i].target.party;
            func_801EFF40();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

INCLUDE_ASM(func_801EED18);

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEF80 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEFC4(void) {
    SYS_DISPATCH_BYTE(D_801F05B8, g_Task->header.step);
    g_Task->param.unk_0B += 1;
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EF54C();
    }
}

INCLUDE_ASM(func_801EF058);

#include "overlays/bmagic/Effect_CountUpTimerByTwoAndStep.h"

MATCH void func_801EF3DC(void) {
    PartyMember* battler;
    u8           slot;
    u8           timer;

    if (g_Task->unk_09 >= 17 && (g_FrameCount & 0x3) == 0) {
        slot                                   = BMagic_AllocEffect();
        battler                                = g_BattleEffectBattler;
        BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[slot].target.party = battler;
        BMAGIC_EFFECT_SLOTS[slot].unk_0B       = RANDOM_MASK(0x1F);
        BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = 1;
        g_BattleEffectBattler->param.unk_0B += 1;
    }
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF4F0(void) {
    PartyMember* work;
    s8           timer;

    work         = g_Task;
    timer        = work->unk_5D - 1;
    work->unk_5D = timer;
    if (timer == 0) {
        work               = g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B - 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF54C);

MATCH void func_801EFF40(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 5), 1, g_Task);
}

INCLUDE_ASM(func_801EFF84);

MATCH void func_801F00D4(void) {
    s32 value;
    s32 value2;
    u8  value3;

    value3         = g_Task->unk_09 - 1;
    g_Task->unk_09 = value3;
    if (!(value3 & BYTE_MASK)) {
        g_Task->unk_14      = 0x40000;
        g_Task->unk_20      = 0x20000;
        value2              = RANDOM_MASK(0xF) + 0x1C;
        value               = (g_Task->param.unk_0B & 0x1F) << 7;
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + (rsin(value) * value2);
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + (rcos(value) * value2);
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
        g_Task->unk_5D      = RANDOM_MASK(7) + 5;
        g_Task->unk_5E      = RANDOM_MASK(7) + 5;
        g_Task->unk_5F      = RANDOM_MASK(7) + 5;
        g_Task->unk_09      = 0x10;
        g_Task->timer       = 16;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F023C(void) {
    PartyMember* work  = g_Task;
    u8           timer = work->unk_09 - 1;
    s32          value = work->unk_14 + work->unk_20;
    work->unk_09       = timer;
    work->unk_14       = value;
    work->pos.z.fixed += value;
    if (timer == 0) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801F029C(void) {
    PartyMember* work  = g_Task;
    u8           timer = work->timer - 1;
    s32          value = work->unk_14 + work->unk_20;
    work->timer        = timer;
    work->unk_14       = value;
    work->pos.z.fixed += value;
    if (timer == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801F030C);

/* func_801F0500 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0564 */
#include "overlays/bmagic/Actor_Clear.h"
