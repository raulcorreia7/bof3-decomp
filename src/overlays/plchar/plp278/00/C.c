#include "plp278_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CFCB4[g_Task->header.step]();
}

#include "overlays/plchar/Char_StartTurnGarr.h"

#include "overlays/plchar/Char_RunStepScriptGarr.h"

MATCH void func_801CE610(void) {
    SYS_DISPATCH_TASK(D_801CFCC0, 2, g_Task);
}

INCLUDE_ASM(func_801CE654);

#include "overlays/plchar/Char_TickPauseTimer.h"

INCLUDE_ASM(func_801CE8AC);

#include "overlays/plchar/Plchar_FollowerInReach.h"

#include "overlays/plchar/Plchar_ProbeFacingFollower.h"

MATCH void func_801CEBFC(void) {
    SYS_DISPATCH_TASK(D_801CFCC8, 2, g_Task);
}

#include "overlays/plchar/Char_StartFacingTurn.h"

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CEE30(void) {
    SYS_DISPATCH_TASK(D_801CFCD4, 2, g_Task);
}

#include "overlays/plchar/Char_WalkStep.h"

INCLUDE_ASM(func_801CF1C0);

#include "overlays/plchar/Char_AdvanceScript.h"

#include "overlays/plchar/Char_ProbeCellSpawn.h"

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801CF858(void) {
    SYS_DISPATCH_TASK(D_801CFCE0, 2, g_Task);
}

#include "overlays/plchar/Char_StartTurn.h"

#include "overlays/plchar/Char_RunStepScriptNinaAdult.h"

MATCH void func_801CFA64(void) {
    SYS_DISPATCH_TASK(D_801CFCEC, 2, g_Task);
}

MATCH void func_801CFAA8(void) {
    u8 slot;

    if (!(g_Task->direction_08 & 1)) {
        g_Task->direction_08 = (g_Task->direction_08 - 1) & 7;
    }
    slot                     = func_8019601C();
    g_Task->param.actor_slot = slot;
    if (g_Task->param.actor_slot != 0xFF) {
        g_ActorSlots[g_Task->param.actor_slot].header.flags = 1;
        g_ActorSlots[g_Task->param.actor_slot].type         = 0x1B;
    }
    Actor_RequestScript((g_Task->direction_08 >> 1) + 0x42);
    /* FAKE: retail reads SND_PlayCue as void(s32). */
    ((void (*)(s32))SND_PlayCue)(g_Task->unk_2C + 0x100);
    g_Task->header.step++;
}

#include "overlays/plchar/Char_ClearModeIfSlotFree.h"

MATCH void func_801CFC2C(void) {
    D_801CFCF4[g_Task->unk_2C]();
}

MATCH void func_801CFC70(void) {
    D_801CFD00[g_Task->unk_2C]();
}
