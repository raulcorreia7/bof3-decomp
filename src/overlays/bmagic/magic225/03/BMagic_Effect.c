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
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
}

INCLUDE_ASM(func_801EF31C);

INCLUDE_ASM(func_801EF404);

MATCH void func_801EF578(void) {
    u8 temp_v1;

    temp_v1                           = g_SpadWork->word_08.byte.timer_0A + 2;
    g_SpadWork->word_08.byte.timer_0A = temp_v1;
    if ((temp_v1 & 0xFF) == 0x10) {
        g_SpadWork->word_08.byte.unk_0B = 0;
        g_SpadWork->unk_02 += 1;
    }
}

#include "overlays/bmagic/Effect_CountUpAndStep.h"

MATCH void func_801EF628(void) {
    if ((u8)D_801EB4E0->word_08.byte.unk_0B < 2U) {
        g_SpadWork->word_08.byte.unk_0B = 1;
        g_SpadWork->unk_02 += 1;
    }
}

INCLUDE_ASM(func_801EF67C);

INCLUDE_ASM(func_801EF7D4);

INCLUDE_ASM(func_801EFCA0);

MATCH void func_801EFE0C(void) {
    SYS_DISPATCH_TASK(D_801F03AC, 1, g_SpadWork);
}

MATCH void func_801EFE50(void) {
    g_ScriptBank = 0x800C3800;
    SYS_DISPATCH_BYTE(D_801F03AC + 1, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_8014D290();
    }
    g_ScriptBank = AREA_SCRIPT_BANK;
}

INCLUDE_ASM(func_801EFEE8);

MATCH void func_801F0140(void) {
    s32 value;

    func_8014D978();
    g_SpadWork->unk_40 += 0x800;
    g_SpadWork->unk_44 += 0x800;
    g_SpadWork->coord_x_34.raw += rsin(g_SpadWork->unk_14) * g_SpadWork->unk_0C;
    g_SpadWork->coord_y_38.raw += rcos(g_SpadWork->unk_14) * g_SpadWork->unk_0C;
    if (g_FrameCount & 1) {
        value = g_SpadWork->unk_0C;
        if (value == 4) {
            g_SpadWork->unk_02 += 1;
            return;
        }
        g_SpadWork->unk_0C = value - 1;
    }
}

INCLUDE_ASM(func_801F021C);

/* func_801F02D4 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0338 */
MATCH void Actor_Clear(void) {
    Bmagic_ResetLocalWork();
}
