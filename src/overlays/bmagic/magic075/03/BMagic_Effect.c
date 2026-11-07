#include "magic075_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC70);

INCLUDE_ASM(func_801EEDE0);

INCLUDE_ASM(func_801EEEB0);

MATCH void func_801EEFF4(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->header.mode);
}

MATCH void func_801EF038(void) {
    g_ScriptBank = 0x800C3800;
    SYS_DISPATCH_BYTE(D_801EF7A0 + 1, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
    }
    g_ScriptBank = AREA_SCRIPT_BANK;
}

INCLUDE_ASM(func_801EF0D0);

MATCH void func_801EF2A8(void) {
    PartyBattler* work;

    if (func_8014DAEC() != 0u) {
        work               = (PartyBattler*)D_801EB4E0;
        work->param.unk_0B = work->param.unk_0B + 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF2F4);

INCLUDE_ASM(func_801EF500);
