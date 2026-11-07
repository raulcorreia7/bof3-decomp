#include "magic167_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_DispatchMode.h"

INCLUDE_ASM(func_801EEC94);

MATCH void func_801EEE88(void) {
    PartyBattler** selected;

    if (--g_Task->unk_09 == 0) {
        selected = &g_BattleSelectedActor;
        GFX_FreePaletteFadeTarget(*selected);
        g_Task->timer  = GFX_AllocPaletteFade((u8*)*selected, 0, 0, 0, 1);
        g_Task->unk_09 = 8;
        g_Task->header.mode++;
    }
}

#include "overlays/bmagic/Effect_BrightenPalette.h"

#include "overlays/bmagic/Effect_Pause.h"

INCLUDE_ASM(func_801EF080);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801EF2D8(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

INCLUDE_ASM(func_801EF31C);

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_StepWhileTickUnderTwo.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801EF4B0);

INCLUDE_ASM(func_801EF708);

INCLUDE_ASM(func_801EF9B8);

MATCH void func_801EFA70(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->timer       = 0x1;
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EFACC(void) {
    u8 timer;

    g_Task->param.unk_0B += 2;
    g_Task->unk_09 += 1;
    timer = g_Task->timer;
    if (timer < 0x10U) {
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
    PartyBattler* work;
    u8            next;

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
