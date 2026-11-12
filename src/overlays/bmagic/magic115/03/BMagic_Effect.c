#include "magic115_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC14.h"

INCLUDE_ASM(func_801EEC80);

MATCH void func_801EEDDC(void) {
    g_PaletteFades[g_Task->timer].offset.red   = g_Task->unk_09 * 2;
    g_PaletteFades[g_Task->timer].offset.green = g_Task->unk_09 * 2;
    g_PaletteFades[g_Task->timer].offset.blue  = g_Task->unk_09 * 2;
    if (g_Task->unk_09 >= 6) {
        g_Task->header.mode++;
    }
}

INCLUDE_ASM(func_801EEEB0);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EF054 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF098(void) {
    g_ScriptTable = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801EF8C0 + 1, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
    }
    g_ScriptTable = AREA_SCRIPT_TABLE;
}

INCLUDE_ASM(func_801EF130);

INCLUDE_ASM(func_801EF27C);

MATCH void func_801EF49C(void) {
    s32  value = -0x80;
    s32* d;
    u8   tick;

    g_Task->unk_5D -= 4;
    g_Task->unk_5E -= 4;
    g_Task->unk_5F -= 4;
    Actor_StepAnimLoop();
    tick                = g_Task->unk_09 + 1;
    g_Task->unk_09      = tick;
    d                   = &D_1F800000;
    d[0]                = BMAGIC_PHASE_ANGLE(tick & BMAGIC_PHASE_MASK);
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + FIXED_MUL(rsin(d[0]), 0xC000);
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + FIXED_MUL(rcos(d[0]), 0xC000);
    g_Task->unk_5D      = value;
    g_Task->header.step += 1;
}

#include "overlays/bmagic/Effect_TickDownAndClear.h"

MATCH void func_801EF5F8(void) {
    g_ScriptTable = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801EF8D0 + 1, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
    }
    g_ScriptTable = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF690(void) {
    g_Task->unk_25      = 0x1D;
    g_Task->unk_26      = 0;
    g_Task->scale.x     = 0x10000;
    g_Task->scale.y     = 0x10000;
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
    g_Task->header.step += 1;
}

MATCH void func_801EF7A4(void) {
    Actor_StepAnimOnce();
    if (Actor_StepAnimOnce() != 0u) {
        g_Task->header.step = g_Task->header.step + 2;
    }
}

MATCH void func_801EF7F4(void) {
    s32 value = -0x80;
    g_Task->unk_5D -= 4;
    g_Task->unk_5E -= 4;
    g_Task->unk_5F -= 4;
    Actor_StepAnimOnce();
    g_Task->unk_5D = value;
    g_Task->header.step += 1;
}

MATCH void Effect_TickDownAndClear2(void) {
    EFFECT_TICK_DOWN_AND_CLEAR();
}
