#include "magic058_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC28);

INCLUDE_ASM(func_801EED30);

MATCH void func_801EEE78(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 0) {
        func_801DE8C0(1, 0x3C, Resource_GetText(0x14U));
        g_SpadWork->step_01 += 1;
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
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EEF74(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_BYTE(handlers.handlers, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0) {
        Effect_SetActorMatrix();
        func_801EF74C();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF008);

INCLUDE_ASM(func_801EF080);

#include "overlays/bmagic/Effect_TickDownAndClear.h"

MATCH void func_801EF36C(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 1), 1, g_SpadWork);
}

MATCH void func_801EF3B0(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC1C;
    SYS_DISPATCH_BYTE(handlers.handlers, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801EFA78();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF454);

MATCH void func_801EF5D4(void) {
    PartyBattler* work;

    work         = g_SpadWork;
    work->unk_0C = work->unk_0C + work->unk_18;
    if (--work->unk_18 == 0x10) {
        work->unk_02++;
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
