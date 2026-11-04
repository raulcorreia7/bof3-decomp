#include "magic058_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC28);

INCLUDE_ASM(func_801EED30);

INCLUDE_ASM(func_801EEE78);

INCLUDE_ASM(func_801EEEDC);

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

MATCH void func_801EF338(void) {
    PartyBattler* work;

    work = (PartyBattler*)D_801EB4E0;
    work->unk_0B--;
    func_801E5988();
}

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

INCLUDE_ASM(func_801EF5D4);

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
