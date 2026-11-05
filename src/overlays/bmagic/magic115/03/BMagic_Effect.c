#include "magic115_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC14.h"

INCLUDE_ASM(func_801EEC80);

INCLUDE_ASM(func_801EEDDC);

INCLUDE_ASM(func_801EEEB0);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EF054(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

MATCH void func_801EF098(void) {
    g_ScriptBank = 0x800C3800;
    SYS_DISPATCH_BYTE(D_801EF8C0 + 1, g_Task->step);
    if (g_Task->flags != 0 && g_Task->step != 0) {
        func_8014D290();
    }
    g_ScriptBank = AREA_SCRIPT_BANK;
}

/* First difference: lui a0 at +0x50; try the work pointer lifetime after the depth copy. */
INCLUDE_ASM(func_801EF130);

INCLUDE_ASM(func_801EF27C);

INCLUDE_ASM(func_801EF49C);

#include "overlays/bmagic/Effect_TickDownAndClear.h"

MATCH void func_801EF5F8(void) {
    g_ScriptBank = 0x800C3800;
    SYS_DISPATCH_BYTE(D_801EF8D0 + 1, g_Task->step);
    if (g_Task->flags != 0 && g_Task->step != 0) {
        func_8014D290();
    }
    g_ScriptBank = AREA_SCRIPT_BANK;
}

MATCH void func_801EF690(void) {
    g_Task->unk_25      = 0x1D;
    g_Task->unk_26      = 0;
    g_Task->unk_40      = 0x10000;
    g_Task->unk_44      = 0x10000;
    g_Task->unk_48      = 1;
    g_Task->unk_27      = 0xA0;
    g_Task->unk_28      = 0;
    g_Task->unk_24      = 4;
    g_Task->unk_5D      = 0;
    g_Task->unk_5E      = 0;
    g_Task->unk_5F      = 0;
    g_Task->unk_5C      = 0;
    g_Task->unk_2A      = 0;
    g_Task->unk_29      = 4;
    g_Task->unk_2C.half = 0;
    g_Task->unk_2B      = 0;
    Actor_SelectScript(1U);
    g_Task->step += 1;
}

MATCH void func_801EF7A4(void) {
    func_8014DAEC();
    if (func_8014DAEC() != 0u) {
        g_Task->step = g_Task->step + 2;
    }
}

MATCH void func_801EF7F4(void) {
    s32 value = -0x80;
    g_Task->unk_5D -= 4;
    g_Task->unk_5E -= 4;
    g_Task->unk_5F -= 4;
    func_8014DAEC();
    g_Task->unk_5D = value;
    g_Task->step += 1;
}

MATCH void Effect_TickDownAndClear_801EF888(void) {
    EFFECT_TICK_DOWN_AND_CLEAR();
}
