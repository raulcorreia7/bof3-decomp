#include "magic220_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_RunSlots.h"

INCLUDE_ASM(func_801EED18);

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEF78 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEFBC(void) {
    g_ScriptTable = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801F06E0, g_Task->header.step);
    if ((g_Task->header.flags & BMAGIC_EFFECT_IN_USE) != 0 && g_Task->header.step != 0) {
        func_8014D290();
        Effect_SetActiveActorMatrix();
        func_801EF9F0();
        BMagic_DrawDarkRing();
        PopMatrix();
    }
    g_ScriptTable = AREA_SCRIPT_TABLE;
}

/* blocker: work pointer lifetime; first diff: lui v0 at +0x84. */
INCLUDE_ASM(func_801EF078);

MATCH void func_801EF1F4(void) {
    u8 count;

    Actor_StepAnimOnce();
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
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActiveActorMatrix.h"

INCLUDE_ASM(func_801EF9F0);

#include "overlays/bmagic/BMagic_DarkRingQuads.h"

/* func_801EFC40 */
MATCH void BMagic_DrawDarkRing(void) {
    GFX_AddDitheredDrawMode(5, getTPage(0, 2, 320, 256));
    D_1F800000.view.effect.params[0] = g_Task->param.unk_0B;
    D_1F800000.view.effect.params[1] = g_Task->param.unk_0B * 2;
    D_1F800000.view.effect.params[5] = (s8)g_Task->unk_5D * 4;
    BMAGIC_DRAW_DARK_RING_QUADS(5, 5);
}

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

/* The y position loads g_BattleEffectBattler before the rcos multiply; retail multiplies first (first diff at 0x801F0094). The x position matches. */
INCLUDE_ASM(func_801F002C);

/* Retail reloads g_Task after the rsin call and before the 24x multiply; the draft multiplies first (first diff at 0x801F0140). Needs the extern D_1F800004 (u16) in magic220_03.h. */
INCLUDE_ASM(func_801F010C);

INCLUDE_ASM(func_801F01C8);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801F0334);

/* func_801F0628 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F068C */
#include "overlays/bmagic/Actor_Clear.h"
