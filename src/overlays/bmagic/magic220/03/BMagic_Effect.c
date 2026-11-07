#include "magic220_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC10);

INCLUDE_ASM(func_801EED18);

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEF78(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

MATCH void func_801EEFBC(void) {
    g_ScriptBank = 0x800C3800;
    SYS_DISPATCH_BYTE(D_801F06E0, g_Task->header.step);
    if ((g_Task->header.flags & BMAGIC_EFFECT_IN_USE) != 0 && g_Task->header.step != 0) {
        func_8014D290();
        Effect_SetActiveActorMatrix();
        func_801EF9F0();
        func_801EFC40();
        PopMatrix();
    }
    g_ScriptBank = AREA_SCRIPT_BANK;
}


/* blocker: work pointer lifetime; first diff: lui v0 at +0x84. */
INCLUDE_ASM(func_801EF078);

MATCH void func_801EF1F4(void) {
    u8 count;

    func_8014DAEC();
    g_Task->param.unk_0B += 0xC;
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_Task->unk_09 = 0x1E;
        g_Task->timer  = 3;
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EF294);

/* blocker: y register merge; first diff: lw v0,56(a1) (retail) against lw v1,56(a1) (candidate). */
INCLUDE_ASM(func_801EF40C);

INCLUDE_ASM(func_801EF4EC);

INCLUDE_ASM(func_801EF6B8);

#include "overlays/bmagic/Effect_StepWhileTickUnderThree.h"

MATCH void func_801EF8CC(void) {
    s8 count;

    count = g_Task->unk_5D;
    if (count != 0) {
        g_Task->unk_5D = count - 2;
    }
    if (func_8014DAEC() & BYTE_MASK) {
        g_BattleEffectBattler->param.unk_0B -= 1;
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
    SYS_DISPATCH_BYTE(D_801F0704, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
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
    BMagic_ResetLocalWork();
}
