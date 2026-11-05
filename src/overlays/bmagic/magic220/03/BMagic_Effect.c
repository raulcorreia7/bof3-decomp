#include "magic220_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC10);

INCLUDE_ASM(func_801EED18);

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEF78(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

INCLUDE_ASM(func_801EEFBC);

/* First difference: lui v0 at +0x84; try the work pointer lifetime around the scale and flag stores. */
INCLUDE_ASM(func_801EF078);

MATCH void func_801EF1F4(void) {
    u8 temp_v0;

    func_8014DAEC();
    g_Task->unk_0B += 0xC;
    temp_v0        = g_Task->unk_09 - 1;
    g_Task->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_Task->unk_09 = 0x1E;
        g_Task->timer  = 3;
        g_Task->step += 1;
    }
}

INCLUDE_ASM(func_801EF294);

/* Orbit step: on odd frames the effect sits at the caster (D_801EB4E0) plus (+unk_0C, -unk_0C), otherwise minus (+unk_0C), then unk_09 counts down and reloads 8 while unk_02 steps back. Tried the m2c
 * merged y local (s32/u32/s16/u8), a work pointer set in each branch and a caster local: first differing instruction lw v0,56(a1) retail against lw v1,56(a1) (retail merges y into v0 and stores through a0; the candidate is 4 bytes shorter). */
INCLUDE_ASM(func_801EF40C);

INCLUDE_ASM(func_801EF4EC);

INCLUDE_ASM(func_801EF6B8);

#include "overlays/bmagic/Effect_StepWhileTickUnderThree.h"

MATCH void func_801EF8CC(void) {
    s8 temp_v0;

    temp_v0 = (s8)g_Task->unk_5D;
    if (temp_v0 != 0) {
        g_Task->unk_5D = temp_v0 - 2;
    }
    if (func_8014DAEC() & 0xFF) {
        D_801EB4E0->unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActiveActorMatrix.h"

INCLUDE_ASM(func_801EF9F0);

INCLUDE_ASM(func_801EFC40);

MATCH void func_801EFF60(void) {
    SYS_DISPATCH_TASK(D_801F0700, 1, g_Task);
}

MATCH void func_801EFFA4(void) {
    SYS_DISPATCH_BYTE(D_801F0704, g_Task->step);
    if (g_Task->flags != 0 && g_Task->step != 0) {
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
