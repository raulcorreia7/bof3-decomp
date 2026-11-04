#include "magic226_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC10);

INCLUDE_ASM(func_801EED18);

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EF004(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EF048);

INCLUDE_ASM(func_801EF10C);

INCLUDE_ASM(func_801EF310);

INCLUDE_ASM(func_801EF540);

INCLUDE_ASM(func_801EF5F0);

INCLUDE_ASM(func_801EF698);

MATCH void func_801EF75C(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    BMAGIC_SET_ACTOR_MATRIX_SPAN(BATTLE_ACTIVE_WORK);
}

INCLUDE_ASM(func_801EF814);

INCLUDE_ASM(func_801EFA64);

MATCH void func_801EFD84(void) {
    SYS_DISPATCH_TASK(D_801F0C60, 1, g_SpadWork);
}

MATCH void func_801EFDC8(void) {
    SYS_DISPATCH_BYTE(D_801F0C78, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_800AF764();
        func_801F01B8();
    }
}

INCLUDE_ASM(func_801EFE48);

INCLUDE_ASM(func_801EFF88);

INCLUDE_ASM(func_801F00B0);

INCLUDE_ASM(func_801F01B8);

MATCH void func_801F04D4(void) {
    SYS_DISPATCH_BYTE(D_801F0C84, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801F07D4();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801F055C);

INCLUDE_ASM(func_801F061C);

INCLUDE_ASM(func_801F068C);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801F07D4);

/* func_801F0B8C */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0BF0 */
MATCH void Actor_Clear(void) {
    Bmagic_ResetLocalWork();
}
