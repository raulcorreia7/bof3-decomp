#include "magic004_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC28.h"

INCLUDE_ASM(func_801EEC98);

INCLUDE_ASM(func_801EEF8C);

MATCH void func_801EF158(void) {
    u16 cue;

    if (g_SpadWork->word_08.byte.unk_0B == 0) {
        cue = D_801EFE40[g_SpadWork->unk_04];
        if (cue != 0) {
            SND_QueueSelectionFx(cue);
        }
        func_800A9820(g_BattleTargetSelector);
        g_SpadWork->word_08.byte.unk_09 = 0;
        g_SpadWork->step_01++;
    }
}

INCLUDE_ASM(func_801EF1F0);

INCLUDE_ASM(func_801EF3E0);

INCLUDE_ASM(func_801EF490);

INCLUDE_ASM(func_801EF6E0);

MATCH void func_801EF8CC(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EF910);

#include "overlays/bmagic/Effect_ReloadTimerAndStep.h"

INCLUDE_ASM(func_801EF9E8);

#include "overlays/bmagic/Effect_LowerTickerStepOnReady.h"

MATCH void func_801EFAD4(void) {
    func_801E5988();
}

INCLUDE_ASM(func_801EFAF4);

#include "overlays/bmagic/Effect_StepWhileTickUnderTwo.h"

INCLUDE_ASM(func_801EFBEC);

INCLUDE_ASM(func_801EFD84);
