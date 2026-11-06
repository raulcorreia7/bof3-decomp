#include "magic081_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(CardAccessFile);

INCLUDE_ASM(func_801EED44);

MATCH void func_801EEE74(void) {
    PartyBattler* saved;

    saved  = g_Task;
    g_Task = D_801EC2E0->target.party;
    if (func_8014DAEC() & BYTE_MASK) {
        saved->header.mode++;
    }
    g_Task = saved;
}

INCLUDE_ASM(func_801EEEDC);

MATCH void func_801EEF88(void) {
    PartyBattler* saved_work;

    saved_work = g_Task;
    g_Task     = D_801EC2E0->target.party;
    func_8014DAEC();
    g_Task = saved_work;
    if (saved_work->unk_0B == 0) {
        func_800A9820(g_BattleTargetSelector);
        g_BattleState |= 4;
        func_801E5988();
    }
}

MATCH void func_801EF014(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->header.mode);
}

MATCH void func_801EF058(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC14;
    SYS_DISPATCH_TASK(handlers.handlers, 2, g_Task);
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
    SYS_DISPATCH_TASK(handlers.handlers, 2, g_Task);
}

INCLUDE_ASM(func_801EF39C);

MATCH void func_801EF44C(void) {
    s32 temp_a0;
    s32 temp_v0;
    u8  temp_v0_2;

    temp_v0        = (g_Task->unk_09 + g_Task->unk_0B) & 0x3F;
    SP_REF(s16, 2) = (temp_v0 << 6);
    temp_a0        = g_Task->unk_14 + ((rsin((s16)(temp_v0 << 6)) * 0x12C) >> 0xC);
    g_Task->unk_0C = temp_a0;
    g_Task->pos.x.fixed += (rsin(temp_a0) * 0x7000) >> 0xC;
    g_Task->pos.y.fixed += (rcos(g_Task->unk_0C) * 0x7000) >> 0xC;
    func_800AF764();
    func_801EF6A0();
    temp_v0_2      = g_Task->unk_09 + 1;
    g_Task->unk_09 = temp_v0_2;
    if ((temp_v0_2 & 0xFF) == 0x10) {
        g_Task->timer = 0x40;
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EF57C);

MATCH void func_801EF614(void) {
    func_800AF764();
    func_801EF6A0();
    BATTLE_ACTIVE_WORK->unk_0B -= 1;
    g_Task->header.flags = 0;
    g_Task->header.mode  = 0;
    g_Task->header.step  = 0;
    g_Task->unk_03       = 0;
    g_Task->unk_04       = 0;
}

INCLUDE_ASM(func_801EF6A0);

/* func_801EFA20 */
#include "overlays/bmagic/BMagic_AllocEffect.h"
