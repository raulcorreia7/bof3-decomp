#include "magic058_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC28);

INCLUDE_ASM(func_801EED30);

MATCH void func_801EEE78(void) {
    if (g_Task->unk_0B == 0) {
        func_801DE8C0(1, 0x3C, Resource_GetText(0x14U));
        g_Task->mode += 1;
    }
}

MATCH void func_801EEEDC(void) {
    if (D_801EC2E4 == 0) {
        func_800A9820(g_BattleTargetSelector);
        g_BattleState |= 4;
        func_801E5988();
    }
}

MATCH void func_801EEF30(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

MATCH void func_801EEF74(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->step);
    if (g_Task->flags != 0) {
        Effect_SetActorMatrix();
        func_801EF74C();
        PopMatrix();
    }
}

MATCH void func_801EF008(void) {
    PartyBattler* work;
    PartyBattler* actor;
    s32           z;

    g_Task->facing    = D_801EB4E0->facing;
    work              = g_Task;
    actor             = D_801EB4E0;
    work->pos.x.fixed = actor->pos.x.fixed;
    work->pos.y.fixed = actor->pos.y.fixed;
    z                 = actor->pos.z.fixed;
    work->timer       = 0x10;
    work->unk_0C      = 8;
    work->pos.z.fixed = z;
    g_Task->step += 1;
}

INCLUDE_ASM(func_801EF080);

#include "overlays/bmagic/Effect_TickDownAndClear.h"

MATCH void func_801EF36C(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 1), 1, g_Task);
}

MATCH void func_801EF3B0(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC1C;
    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->step);
    if (g_Task->flags != 0 && g_Task->step != 0) {
        Effect_SetActorMatrix();
        func_801EFA78();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF454);

MATCH void func_801EF5D4(void) {
    PartyBattler* work;

    work         = g_Task;
    work->unk_0C = work->unk_0C + work->unk_18;
    if (--work->unk_18 == 0x10) {
        work->step++;
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
MATCH void Actor_Clear(void) {
    Bmagic_ResetLocalWork();
}
