#include "magic220_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC10);

INCLUDE_ASM(func_801EED18);

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEF78(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EEFBC);

INCLUDE_ASM(func_801EF078);

INCLUDE_ASM(func_801EF1F4);

INCLUDE_ASM(func_801EF294);

INCLUDE_ASM(func_801EF40C);

INCLUDE_ASM(func_801EF4EC);

INCLUDE_ASM(func_801EF6B8);

#include "overlays/bmagic/Effect_StepWhileTickUnderThree.h"

INCLUDE_ASM(func_801EF8CC);

MATCH void func_801EF938(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    BMAGIC_SET_ACTOR_MATRIX_SPAN(BATTLE_ACTIVE_WORK);
}

INCLUDE_ASM(func_801EF9F0);

INCLUDE_ASM(func_801EFC40);

MATCH void func_801EFF60(void) {
    SYS_DISPATCH_TASK(D_801F0700, 1, g_SpadWork);
}

MATCH void func_801EFFA4(void) {
    SYS_DISPATCH_BYTE(D_801F0704, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801F0334();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801F002C);

INCLUDE_ASM(func_801F010C);

INCLUDE_ASM(func_801F01C8);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801F0334);

/* func_801F0628 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F068C */
MATCH void Actor_Clear(void) {
    Bmagic_ResetLocalWork();
}
