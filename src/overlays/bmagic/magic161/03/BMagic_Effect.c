#include "magic161_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC84);

MATCH void func_801EEE9C(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 0) {
        D_801EB4E0->flags_00 &= 0xBF;
        func_800AEF98(0x18, 0);
        g_SpadWork->step_01 += 1;
    }
}

#include "shared/Effect_StartPlaying.h"

MATCH s32 func_801EEF3C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
}

MATCH void func_801EEF80(void) {
    BattleHandlerTable5 handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_BYTE(handlers.handlers, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_8014D290();
    }
}

#include "overlays/bmagic/Effect_ReloadTimerAndStep.h"

MATCH void func_801EF06C(void) {
    u8 temp_v0;

    func_8014DAEC();
    temp_v0                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        func_800AFC98(2, 4);
        func_800A9820(g_BattleTargetSelector);
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EF0E8(void) {
    u8 count;

    count = g_SpadWork->word_08.byte.unk_09;
    if ((count & 0xFF) == 0x10) {
        SND_QueueSelectionFx(0x100);
        g_SpadWork->unk_02 += 1;
    } else {
        g_SpadWork->word_08.byte.unk_09 = count + 4;
    }
    func_801EF1DC();
    func_8014DAEC();
}

#include "overlays/bmagic/Effect_LowerTickerStepOnReady.h"

MATCH void func_801EF1BC(void) {
    func_801E5988();
}

INCLUDE_ASM(func_801EF1DC);
