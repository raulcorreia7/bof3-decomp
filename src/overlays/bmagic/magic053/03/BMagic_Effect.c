#include "magic053_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC10);

INCLUDE_ASM(func_801EED18);

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EF064(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
}

INCLUDE_ASM(func_801EF0A8);

INCLUDE_ASM(func_801EF174);

INCLUDE_ASM(func_801EF420);

MATCH void func_801EF5C0(void) {
    s16* state;
    u16  var_v0;
    u8   temp_v0;

    func_8014DAEC();
    if (g_SpadWork->word_08.byte.unk_09 & 1) {
        state  = &g_AreaCameraAngle.vx;
        var_v0 = *state + 0x14;
    } else {
        state  = &g_AreaCameraAngle.vx;
        var_v0 = *state - 0x14;
    }
    *state                          = var_v0;
    temp_v0                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_AreaCameraAngle.vx = -0x2AAU;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EF674(void) {
    u8 temp_v0;

    temp_v0 = g_SpadWork->word_08.byte.timer_0A;
    if (temp_v0 != 0) {
        g_SpadWork->word_08.byte.timer_0A = temp_v0 - 2;
    }
    if (func_8014DAEC() & 0xFF) {
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EF6D8(void) {
    PartyBattler* work;

    if (g_SpadWork->unk_04 == 0) {
        work                      = (PartyBattler*)D_801EB4E0;
        work->word_08.byte.unk_0B = work->word_08.byte.unk_0B - 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActiveActorMatrix.h"

INCLUDE_ASM(func_801EF7E0);

INCLUDE_ASM(func_801EFA30);

MATCH void func_801EFD50(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 6), 1, g_SpadWork);
}

MATCH void func_801EFD94(void) {
    SYS_DISPATCH_BYTE(D_801F056C, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801F01C0();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EFE1C);

INCLUDE_ASM(func_801EFF24);

INCLUDE_ASM(func_801F0018);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801F01C0);

/* func_801F0494 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F04F8 */
MATCH void Actor_Clear(void) {
    Bmagic_ResetLocalWork();
}
