#include "magic021_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC28);

INCLUDE_ASM(func_801EED30);

#include "overlays/bmagic/Effect_ReleaseActiveBattlerOnTickerZero.h"

#include "shared/Effect_StartPlaying.h"

MATCH void func_801EEFDC(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

INCLUDE_ASM(func_801EF020);

#include "overlays/bmagic/Effect_ReloadTimerAndStep.h"

INCLUDE_ASM(func_801EF104);

MATCH void func_801EF208(void) {
    if (func_8014DAEC() != 0u) {
        func_800A9820(g_BattleTargetSelector);
        g_Task->step = g_Task->step + 1;
    }
}

MATCH void func_801EF260(void) {
    if ((u8)g_Task->word_08.byte.unk_09 < 0xCU) {
        func_801EF348();
        g_Task->word_08.byte.unk_09 += 4;
        return;
    }
    g_Task->step += 1;
}

MATCH void func_801EF2CC(void) {
    if (g_Task->word_08.byte.unk_0B == 0) {
        D_801EB4E0->word_08.byte.unk_0B -= 1;
        g_Task->step += 1;
    }
}

MATCH void func_801EF328(void) {
    func_801E5988();
}

INCLUDE_ASM(func_801EF348);

MATCH void func_801EF534(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 1), 1, g_Task);
}

MATCH void func_801EF578(void) {
    SYS_DISPATCH_BYTE(D_801EFE08, g_Task->step);
    if (g_Task->flags != 0 && g_Task->step != 0) {
        func_800AF764();
        func_801EF7FC();
        func_801EFA48();
    }
}

INCLUDE_ASM(func_801EF600);

#include "overlays/bmagic/Effect_CountUpByTwoAndStep.h"

MATCH void func_801EF7A0(void) {
    PartyBattler* work;

    work                        = g_Task;
    work->word_08.byte.timer_0A = work->word_08.byte.timer_0A - 2;
    if (work->word_08.byte.timer_0A == 0) {
        work                      = (PartyBattler*)D_801EB4E0;
        work->word_08.byte.unk_0B = work->word_08.byte.unk_0B - 1;
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
