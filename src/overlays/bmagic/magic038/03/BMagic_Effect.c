#include "magic038_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC70);

INCLUDE_ASM(func_801EEE14);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH void func_801EF0D0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->header.mode);
}

MATCH void func_801EF114(void) {
    g_ScriptBank = 0x800C3800;
    SYS_DISPATCH_BYTE(D_801EF9A8 + 1, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
    }
    g_ScriptBank = AREA_SCRIPT_BANK;
}

INCLUDE_ASM(func_801EF1AC);

INCLUDE_ASM(func_801EF3BC);

INCLUDE_ASM(func_801EF590);

INCLUDE_ASM(func_801EF710);

#include "overlays/bmagic/Effect_TickDownAndClear.h"

MATCH void func_801EF8B8(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 11), 2, g_Task);
}

#include "overlays/bmagic/Effect_RequestQueueEntryAndArmTicker.h"

#include "overlays/bmagic/Effect_TickOnZeroTick.h"
