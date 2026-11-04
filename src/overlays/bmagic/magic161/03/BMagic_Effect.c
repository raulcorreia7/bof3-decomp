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

INCLUDE_ASM(func_801EF0E8);

MATCH void func_801EF158(void) {
    if (func_8014DAEC() & BYTE_MASK) {
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B--;
        g_SpadWork->unk_02++;
    }
}

MATCH void func_801EF1BC(void) {
    func_801E5988();
}

INCLUDE_ASM(func_801EF1DC);
