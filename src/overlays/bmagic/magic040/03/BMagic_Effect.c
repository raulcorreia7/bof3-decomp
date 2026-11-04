#include "magic040_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC80);

INCLUDE_ASM(func_801EEDFC);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH void func_801EEF48(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EEF8C);

MATCH void func_801EF074(void) {
    g_SpadWork->word_08.byte.facing_08 = BATTLE_ACTIVE_WORK->word_08.byte.facing_08;
    g_SpadWork->coord_x_34.raw         = BATTLE_ACTIVE_WORK->coord_x_34.raw;
    g_SpadWork->coord_y_38.raw         = BATTLE_ACTIVE_WORK->coord_y_38.raw;
    g_SpadWork->word_3C.word           = BATTLE_ACTIVE_WORK->word_3C.word;
    func_801EF430(g_SpadWork);
    g_SpadWork->word_08.byte.unk_09   = 0;
    g_SpadWork->word_08.byte.timer_0A = 0;
    g_SpadWork->unk_02 += 1;
}

#include "overlays/bmagic/Effect_CountUpTimersAndStep.h"

#include "overlays/bmagic/Effect_CountUpAndStepAt32.h"

#include "overlays/bmagic/Effect_CountDownTimer.h"

INCLUDE_ASM(func_801EF248);

INCLUDE_ASM(func_801EF2D8);

MATCH void func_801EF388(void) {
    g_SpadWork->word_08.byte.unk_0B -= 1;
    g_SpadWork->word_08.byte.unk_09 += g_SpadWork->word_08.byte.unk_0B;
    g_SpadWork->word_08.byte.timer_0A -= 0xC;
    if (g_SpadWork->word_08.byte.unk_0B == 0) {
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B -= 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF430);

INCLUDE_ASM(func_801EF600);

INCLUDE_ASM(func_801EF7FC);

INCLUDE_ASM(func_801EFA3C);
