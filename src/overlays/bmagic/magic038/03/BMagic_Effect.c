#include "magic038_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC70);

INCLUDE_ASM(func_801EEE14);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH void func_801EF0D0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
}

INCLUDE_ASM(func_801EF114);

INCLUDE_ASM(func_801EF1AC);

INCLUDE_ASM(func_801EF3BC);

INCLUDE_ASM(func_801EF590);

INCLUDE_ASM(func_801EF710);

#include "overlays/bmagic/Effect_TickDownAndClear.h"

MATCH void func_801EF8B8(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 11), 2, g_SpadWork);
}

#include "overlays/bmagic/Effect_RequestQueueEntryAndArmTicker.h"

#include "overlays/bmagic/Effect_TickOnZeroTick.h"
