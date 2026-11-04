#include "magic219_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC14);

INCLUDE_ASM(func_801EED28);

INCLUDE_ASM(func_801EEE50);

INCLUDE_ASM(func_801EEF54);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EF024(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EF068);

INCLUDE_ASM(func_801EF118);

INCLUDE_ASM(func_801EF3CC);

INCLUDE_ASM(func_801EF530);

INCLUDE_ASM(func_801EF5DC);

MATCH void func_801EF664(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    BMAGIC_SET_ACTOR_MATRIX_SPAN(BATTLE_ACTIVE_WORK);
}

INCLUDE_ASM(func_801EF71C);

/* func_801EF934 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801EF998 */
MATCH void Actor_Clear(void) {
    Bmagic_ResetLocalWork();
}
