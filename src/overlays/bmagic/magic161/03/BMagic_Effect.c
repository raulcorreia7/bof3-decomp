#include "magic161_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC84);

INCLUDE_ASM(func_801EEE9C);

#include "shared/Effect_StartPlaying.h"

MATCH void func_801EEF3C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
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

INCLUDE_ASM(func_801EF06C);

MATCH void func_801EF0E8(void) {
    u8 temp_a0;

    temp_a0 = g_SpadWork->word_08.byte.unk_09;
    if ((temp_a0 & 0xFF) == 0x10) {
        SND_QueueSelectionFx(0x100);
        g_SpadWork->unk_02 += 1;
    } else {
        g_SpadWork->word_08.byte.unk_09 = temp_a0 + 4;
    }
    func_801EF1DC();
    func_8014DAEC();
}

#include "overlays/bmagic/Effect_LowerTickerStepOnReady.h"

MATCH void func_801EF1BC(void) {
    func_801E5988();
}

INCLUDE_ASM(func_801EF1DC);
