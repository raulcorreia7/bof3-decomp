#include "magic081_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(CardAccessFile);

INCLUDE_ASM(func_801EED44);

MATCH void func_801EEE74(void) {
    PartyBattler* saved;

    saved      = g_SpadWork;
    g_SpadWork = D_801EC2E0->target.party;
    if (func_8014DAEC() & BYTE_MASK) {
        saved->step_01++;
    }
    g_SpadWork = saved;
}

INCLUDE_ASM(func_801EEEDC);

MATCH void func_801EEF88(void) {
    PartyBattler* saved_work;

    saved_work = g_SpadWork;
    g_SpadWork = D_801EC2E0->target.party;
    func_8014DAEC();
    g_SpadWork = saved_work;
    if (saved_work->word_08.byte.unk_0B == 0) {
        func_800A9820(g_BattleTargetSelector);
        g_BattleState |= 4;
        func_801E5988();
    }
}

MATCH void func_801EF014(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
}

MATCH void func_801EF058(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC14;
    SYS_DISPATCH_TASK(handlers.handlers, 2, g_SpadWork);
}

INCLUDE_ASM(func_801EF0B8);

INCLUDE_ASM(func_801EF18C);

#include "overlays/bmagic/Effect_TickOnZeroTick.h"

MATCH void func_801EF2F0(void) {
    if (g_BattleState & BATTLE_STATE_EFFECT_PLAYING) {
        func_801E5988();
    } else {
        func_800AFD9C();
    }
}

MATCH void func_801EF330(void) {
    MagicTaskFuncs handlers;

    handlers = D_801EEC20;
    SYS_DISPATCH_TASK(handlers.handlers, 2, g_SpadWork);
}

INCLUDE_ASM(func_801EF39C);

MATCH void func_801EF44C(void) {
    s32 temp_a0;
    s32 temp_v0;
    u8  temp_v0_2;

    temp_v0            = (g_SpadWork->word_08.byte.unk_09 + g_SpadWork->word_08.byte.unk_0B) & 0x3F;
    SP_REF(s16, 2)     = (s16)(temp_v0 << 6);
    temp_a0            = g_SpadWork->unk_14 + ((s32)(rsin((s16)(temp_v0 << 6)) * 0x12C) >> 0xC);
    g_SpadWork->unk_0C = temp_a0;
    g_SpadWork->coord_x_34.raw += (s32)(rsin(temp_a0) * 0x7000) >> 0xC;
    g_SpadWork->coord_y_38.raw += (s32)(rcos(g_SpadWork->unk_0C) * 0x7000) >> 0xC;
    func_800AF764(g_SpadWork);
    func_801EF6A0();
    temp_v0_2                       = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0_2;
    if ((temp_v0_2 & 0xFF) == 0x10) {
        g_SpadWork->word_08.byte.timer_0A = 0x40;
        g_SpadWork->unk_02 += 1;
    }
}

INCLUDE_ASM(func_801EF57C);

MATCH void func_801EF614(void) {
    func_800AF764();
    func_801EF6A0();
    BATTLE_ACTIVE_WORK->word_08.byte.unk_0B -= 1;
    g_SpadWork->flags_00 = 0;
    g_SpadWork->step_01  = 0;
    g_SpadWork->unk_02   = 0;
    g_SpadWork->unk_03   = 0;
    g_SpadWork->unk_04   = 0;
}

INCLUDE_ASM(func_801EF6A0);

/* func_801EFA20 */
#include "overlays/bmagic/BMagic_AllocEffect.h"
