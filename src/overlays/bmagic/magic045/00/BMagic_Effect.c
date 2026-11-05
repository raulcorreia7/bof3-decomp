#include "magic045_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback table[2] = {func_801EEC5C, func_801EEE58};

    table[SP_REF(u8*, 0x44)[1]]();
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH void func_801EEEA4(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
}

MATCH void func_801EEEE8(void) {
    g_ScriptBank = 0x800C3800;
    SYS_DISPATCH_BYTE(D_801EF8DC + 1, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_8014D290();
    }
    g_ScriptBank = AREA_SCRIPT_BANK;
}

INCLUDE_ASM(func_801EEF80);

INCLUDE_ASM(func_801EF118);

INCLUDE_ASM(func_801EF2B0);

#include "overlays/bmagic/Effect_TickDownAndClear.h"

MATCH void func_801EF40C(void) {
    g_ScriptBank = 0x800C3800;
    SYS_DISPATCH_BYTE(D_801EF8EC + 1, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_8014D290();
    }
    g_ScriptBank = AREA_SCRIPT_BANK;
}

INCLUDE_ASM(func_801EF4A4);

INCLUDE_ASM(func_801EF608);

INCLUDE_ASM(func_801EF724);

MATCH void Effect_TickDownAndClear_801EF8A4(void) {
    EFFECT_TICK_DOWN_AND_CLEAR();
}
