#include "magic223_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC10);

INCLUDE_ASM(func_801EED18);

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

/* blocker: flags pointer placement; first diff: address load at 0x801EEFC8. */
INCLUDE_ASM(func_801EEFB4);

MATCH void func_801EF00C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, TASK_BYTES[1]);
}

MATCH void func_801EF050(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectFuncs + 1, 2, g_Task);
    if (g_Task->flags != 0) {
        func_801EF1E8();
    }
}

#include "overlays/bmagic/Effect_ArmCounterNextStep.h"

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_StepWhileTickUnderTwo.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801EF1E8);

MATCH void func_801EF3C0(void) {
    SYS_DISPATCH_TASK(D_801EFC40, 1, g_Task);
}

MATCH void func_801EF404(void) {
    SYS_DISPATCH_BYTE(D_801EFC44, g_Task->step);
    if (g_Task->flags != 0 && g_Task->step != 0) {
        func_801EF7A8();
    }
}

INCLUDE_ASM(func_801EF47C);

MATCH void func_801EF628(void) {
    s32 offset;
    u8  timer;

    g_Task->unk_2E.half += (rsin(g_Task->unk_14) * 8) >> 0xC;
    offset = (rcos(g_Task->unk_14) * 8) >> 0xC;
    g_Task->unk_30.half += offset;
    g_Task->unk_09 += 1;
    timer         = g_Task->timer + 4;
    g_Task->timer = timer;
    if ((timer & BYTE_MASK) == 0x10) {
        g_Task->step += 1;
    }
}

MATCH void func_801EF6E0(void) {
    s32 cosine;

    g_Task->unk_2E.half += (rsin(g_Task->unk_14) * 0x18) >> 0xC;
    cosine = rcos(g_Task->unk_14);
    g_Task->unk_30.half += (cosine * 0x18) >> 0xC;
    g_Task->unk_09 += 1;
    if (g_Task->unk_09 == 0x14) {
        D_801EB4E0->unk_0B -= 1;
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801EF7A8);

/* func_801EFB78 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801EFBDC */
MATCH void Actor_Clear(void) {
    Bmagic_ResetLocalWork();
}
