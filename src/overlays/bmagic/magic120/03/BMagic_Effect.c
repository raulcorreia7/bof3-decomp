#include "magic120_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

INCLUDE_ASM(func_801EEC70);

INCLUDE_ASM(func_801EEEC8);

#include "overlays/bmagic/Effect_PlayOnIdleTick.h"

MATCH void func_801EF010(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, TASK_BYTES[1]);
}

/* func_801EF054 */
MATCH void BMagic_UpdateWhelpBreath(void) {
    SYS_DISPATCH_BYTE(D_801F0CB0, g_Task->header.step);
    if (g_BattleEffectBattler->param.unk_0B != 0xFF) {
        if (g_Task->header.step != 0) {
            BMagic_DrawWhelpBreath();
        }
    }
}

INCLUDE_ASM(func_801EF0D8);

MATCH void func_801EF270(void) {
    u8 counter;
    g_Task->timer += 3;
    counter        = g_Task->unk_09 + 1;
    g_Task->unk_09 = counter;
    if ((counter & BYTE_MASK) == 8) {
        g_BattleEffectBattler->param.unk_0B = 1;
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_CountUpTimerCallSelector.h"

#include "overlays/bmagic/Effect_CountUpAndStepAt120.h"

#include "overlays/bmagic/Effect_CountUpAndFinishAt136.h"

INCLUDE_ASM(BMagic_DrawWhelpBreath);

MATCH void func_801EFD20(void) {
    GFX_AddDitheredDrawMode(3, getTPage(0, 0, 320, 256));
    g_ScriptBank = 0x800C3800;
    SYS_DISPATCH_BYTE(D_801F0CC4, g_Task->header.step);
    g_ScriptBank = 0x800D3800;
}

INCLUDE_ASM(func_801EFDD4);

MATCH void func_801F0008(void) {
    func_8014D290();
    if (func_8014DAEC() & BYTE_MASK) {
        func_801E5988();
    }
}

MATCH void func_801F0044(void) {
    u8 temp_v0;

    func_8014D978();
    func_8014D290();
    temp_v0        = g_Task->unk_09 - 1;
    g_Task->unk_09 = temp_v0;
    if (!(temp_v0 & BYTE_MASK)) {
        func_801E5988();
    }
}

MATCH void func_801F009C(void) {
    u8 timer;

    func_801F0274();
    timer          = g_Task->unk_09 + 1;
    g_Task->unk_09 = timer;
    if (timer == 0x60) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801F0104(void) {
    u8 temp_v1;

    func_801F0274();
    temp_v1        = g_Task->unk_09 + 1;
    g_Task->unk_09 = temp_v1;
    if ((temp_v1 & BYTE_MASK) == 0x70) {
        func_801E5988();
    }
}

MATCH void func_801F0158(void) {
    u8 timer;

    func_801F08AC();
    timer          = g_Task->unk_09 + 1;
    g_Task->unk_09 = timer;
    if (timer == 0x10) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801F01C0(void) {
    u8 count;

    func_801F08AC();
    count         = g_Task->timer - 1;
    g_Task->timer = count;
    if (count == 0) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801F0224(void) {
    u8 temp_v0;

    func_801F08AC();
    temp_v0        = g_Task->unk_09 - 1;
    g_Task->unk_09 = temp_v0;
    if (!(temp_v0 & BYTE_MASK)) {
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F0274);

INCLUDE_ASM(func_801F04B0);

INCLUDE_ASM(func_801F078C);

INCLUDE_ASM(func_801F08AC);

INCLUDE_ASM(func_801F0974);

#include "overlays/bmagic/Effect_SetActorMatrix.h"
