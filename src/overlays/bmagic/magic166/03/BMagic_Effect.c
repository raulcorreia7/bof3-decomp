#include "magic166_03.h"

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
    SYS_DISPATCH_BYTE(D_801EF71C, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801EF284();
        func_801EF380();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EEFBC);

INCLUDE_ASM(func_801EF138);

INCLUDE_ASM(func_801EF284);

INCLUDE_ASM(func_801EF380);

/* func_801EF69C */
#include "overlays/bmagic/BMagic_AllocEffect.h"
