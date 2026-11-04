#include "magic021_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC28);

INCLUDE_ASM(func_801EED30);

INCLUDE_ASM(func_801EEF38);

#include "shared/Effect_StartPlaying.h"

MATCH void func_801EEFDC(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EF020);

#include "overlays/bmagic/Effect_ReloadTimerAndStep.h"

INCLUDE_ASM(func_801EF104);

MATCH void func_801EF208(void) {
    if (func_8014DAEC() != 0u) {
        func_800A9820(g_BattleTargetSelector);
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

INCLUDE_ASM(func_801EF260);

INCLUDE_ASM(func_801EF2CC);

MATCH void func_801EF328(void) {
    func_801E5988();
}

INCLUDE_ASM(func_801EF348);

MATCH void func_801EF534(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 1), 1, g_SpadWork);
}

MATCH void func_801EF578(void) {
    SYS_DISPATCH_BYTE(D_801EFE08, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_800AF764();
        func_801EF7FC();
        func_801EFA48();
    }
}

INCLUDE_ASM(func_801EF600);

#include "overlays/bmagic/Effect_CountUpByTwoAndStep.h"

MATCH void func_801EF7A0(void) {
    PartyBattler* work;

    work         = g_SpadWork;
    work->unk_0A = work->unk_0A - 2;
    if (work->unk_0A == 0) {
        work         = (PartyBattler*)D_801EB4E0;
        work->unk_0B = work->unk_0B - 1;
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801EF7FC);

INCLUDE_ASM(func_801EFA48);

/* func_801EFD4C */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801EFDB0 */
MATCH void Actor_Clear(void) {
    Bmagic_ResetLocalWork();
}
