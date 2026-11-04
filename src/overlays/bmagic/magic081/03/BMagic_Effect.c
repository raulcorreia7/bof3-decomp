#include "magic081_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(CardAccessFile);

INCLUDE_ASM(func_801EED44);

MATCH void func_801EEE74(void) {
    PartyBattler* saved;

    saved      = g_SpadWork;
    g_SpadWork = D_801EC2E0->work_74.party;
    if (func_8014DAEC() & BYTE_MASK) {
        saved->step_01++;
    }
    g_SpadWork = saved;
}

INCLUDE_ASM(func_801EEEDC);

INCLUDE_ASM(func_801EEF88);

MATCH void func_801EF014(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
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

INCLUDE_ASM(func_801EF44C);

INCLUDE_ASM(func_801EF57C);

INCLUDE_ASM(func_801EF614);

INCLUDE_ASM(func_801EF6A0);

/* func_801EFA20 */
#include "overlays/bmagic/BMagic_AllocEffect.h"
