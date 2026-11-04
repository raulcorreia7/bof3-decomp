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
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EF31C);

INCLUDE_ASM(func_801EF404);

INCLUDE_ASM(func_801EF578);

#include "overlays/bmagic/Effect_CountUpAndStep.h"

INCLUDE_ASM(func_801EF628);

INCLUDE_ASM(func_801EF67C);

INCLUDE_ASM(func_801EF7D4);

INCLUDE_ASM(func_801EFCA0);

MATCH void func_801EFE0C(void) {
    SYS_DISPATCH_TASK(D_801F03AC, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EFE50);

INCLUDE_ASM(func_801EFEE8);

MATCH void func_801F0140(void) {
    s32 temp_v1;

    func_8014D978();
    g_SpadWork->unk_40 += 0x800;
    g_SpadWork->unk_44 += 0x800;
    g_SpadWork->coord_x_34.raw += rsin(g_SpadWork->unk_14) * g_SpadWork->unk_0C;
    g_SpadWork->coord_y_38.raw += rcos(g_SpadWork->unk_14) * g_SpadWork->unk_0C;
    if (g_FrameCount & 1) {
        temp_v1 = g_SpadWork->unk_0C;
        if (temp_v1 == 4) {
            g_SpadWork->unk_02 += 1;
            return;
        }
        g_SpadWork->unk_0C = temp_v1 - 1;
    }
}

INCLUDE_ASM(func_801F021C);

INCLUDE_ASM(func_801F02D4);

/* func_801F0338 */
MATCH void Actor_Clear(void) {
    Bmagic_ResetLocalWork();
}
