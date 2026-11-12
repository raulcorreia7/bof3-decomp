#include "magic167_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_DispatchMode.h"

INCLUDE_ASM(func_801EEC94);

/* func_801EEE88 */
#include "overlays/bmagic/Effect_PreparePalette.h"

#include "overlays/bmagic/Effect_BrightenPalette.h"

#include "overlays/bmagic/Effect_Pause.h"

/* Darkens the palette fade row the effect timer indexes and, when its red reaches zero, releases the selected
 * battler's fades and advances the mode. */
MATCH void func_801EF080(void) {
    /* FAKE: retail frame reserves 0x10 bytes no statement uses. */
    FAKE_STACK_PADS(u8, 0x10);

    g_PaletteFades[g_Task->timer].offset.red -= 1;
    g_PaletteFades[g_Task->timer].offset.green -= 1;
    g_PaletteFades[g_Task->timer].offset.blue -= 1;
    if (g_PaletteFades[g_Task->timer].offset.red == 0) {
        GFX_FreePaletteFadeTarget(g_Battle.selected_actor);
        func_800AF814(g_Battle.target_selector);
        g_Task->header.mode += 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

/* func_801EF2D8 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF31C(void) {
    SYS_DISPATCH_BYTE(D_801F08B8, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        D_1F800004 = g_Task->unk_09 * 5;
        func_801EF4B0();
        func_801EF708();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_StepWhileTickUnderTwo.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801EF4B0);

INCLUDE_ASM(func_801EF708);

MATCH void func_801EF9B8(void) {
    SYS_DISPATCH_BYTE(D_801F08C4, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        if (g_Task->header.step < 3) {
            func_801EFC44();
        }
        func_801F05C8(2);
        func_801F05C8(3);
        PopMatrix();
    }
}

MATCH void func_801EFA70(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->timer       = 1;
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EFACC(void) {
    u8 timer;

    g_Task->param.unk_0B += 2;
    g_Task->unk_09 += 1;
    timer = g_Task->timer;
    if (timer < 16U) {
        g_Task->timer = timer + 1;
    }
    if (g_Task->unk_09 == 0x18) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFB5C(void) {
    g_Task->param.unk_0B += 2;
    g_Task->unk_09 += 1;
    g_Task->timer -= 1;
    if (g_Task->unk_09 == 0x28) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFBE4(void) {
    PartyMember* work;
    u8           next;

    work        = g_Task;
    next        = work->timer + 1;
    work->timer = next;
    if (next == 0x18) {
        g_BattleEffectBattler->param.unk_0B--;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EFC44);

INCLUDE_ASM(func_801F05C8);
