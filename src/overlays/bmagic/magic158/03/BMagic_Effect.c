#include "magic158_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC04);

INCLUDE_ASM(func_801EED04);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEEF0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EEF34(void) {
    SYS_DISPATCH_BYTE(D_801EF788, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801EF2F0();
        func_801EF3EC();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EEFBC);

INCLUDE_ASM(func_801EF140);

INCLUDE_ASM(func_801EF1C8);

INCLUDE_ASM(func_801EF2F0);

INCLUDE_ASM(func_801EF3EC);

/* func_801EF708 */
#include "overlays/bmagic/BMagic_AllocEffect.h"
