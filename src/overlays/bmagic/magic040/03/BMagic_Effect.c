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

INCLUDE_ASM(func_801EF074);

#include "overlays/bmagic/Effect_CountUpTimersAndStep.h"

#include "overlays/bmagic/Effect_CountUpAndStepAt32.h"

#include "overlays/bmagic/Effect_CountDownTimer.h"

INCLUDE_ASM(func_801EF248);

INCLUDE_ASM(func_801EF2D8);

INCLUDE_ASM(func_801EF388);

INCLUDE_ASM(func_801EF430);

INCLUDE_ASM(func_801EF600);

INCLUDE_ASM(func_801EF7FC);

INCLUDE_ASM(func_801EFA3C);
