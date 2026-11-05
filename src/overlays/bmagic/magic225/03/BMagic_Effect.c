#include "magic225_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC14);

INCLUDE_ASM(func_801EED28);

INCLUDE_ASM(func_801EEE8C);

INCLUDE_ASM(func_801EEF8C);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EF2D8(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

INCLUDE_ASM(func_801EF31C);

INCLUDE_ASM(func_801EF404);

MATCH void func_801EF578(void) {
    u8 temp_v1;

    temp_v1       = g_Task->timer + 2;
    g_Task->timer = temp_v1;
    if ((temp_v1 & 0xFF) == 0x10) {
        g_Task->unk_0B = 0;
        g_Task->step += 1;
    }
}

#include "overlays/bmagic/Effect_CountUpAndStep.h"

MATCH void func_801EF628(void) {
    if ((u8)D_801EB4E0->unk_0B < 2U) {
        g_Task->unk_0B = 1;
        g_Task->step += 1;
    }
}

INCLUDE_ASM(func_801EF67C);

INCLUDE_ASM(func_801EF7D4);

INCLUDE_ASM(func_801EFCA0);

MATCH void func_801EFE0C(void) {
    SYS_DISPATCH_TASK(D_801F03AC, 1, g_Task);
}

MATCH void func_801EFE50(void) {
    g_ScriptBank = 0x800C3800;
    SYS_DISPATCH_BYTE(D_801F03AC + 1, g_Task->step);
    if (g_Task->flags != 0 && g_Task->step != 0) {
        func_8014D290();
    }
    g_ScriptBank = AREA_SCRIPT_BANK;
}

INCLUDE_ASM(func_801EFEE8);

MATCH void func_801F0140(void) {
    s32 value;

    func_8014D978();
    g_Task->unk_40 += 0x800;
    g_Task->unk_44 += 0x800;
    g_Task->coord_x_34.raw += rsin(g_Task->unk_14) * g_Task->unk_0C;
    g_Task->coord_y_38.raw += rcos(g_Task->unk_14) * g_Task->unk_0C;
    if (g_FrameCount & 1) {
        value = g_Task->unk_0C;
        if (value == 4) {
            g_Task->step += 1;
            return;
        }
        g_Task->unk_0C = value - 1;
    }
}

/* First difference at 0x801F0278: work pointer in a0 instead of a1; adjust local lifetimes. */
INCLUDE_ASM(func_801F021C);

/* func_801F02D4 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0338 */
MATCH void Actor_Clear(void) {
    Bmagic_ResetLocalWork();
}
