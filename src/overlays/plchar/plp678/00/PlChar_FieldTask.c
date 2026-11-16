#include "plp678_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D0564[g_Task->header.step]();
}

#include "overlays/plchar/PlChar_StartTurn.h"

#include "overlays/plchar/PlChar_RunStepScript.h"

MATCH void func_801CE610(void) {
    Actor_StepAnimLoop();
}

MATCH void func_801CE630(void) {
    SYS_DISPATCH_TASK(D_801D0570, 2, g_Task);
}

MATCH void func_801CE674(void) {
    SYS_DISPATCH_TASK(D_801D0578, 3, g_Task);
}

/* func_801CE6B8 */
MATCH void PlChar_FaceFreeDirection(void) {
    CHAR_FACE_FREE_DIRECTION(func_801CF1A4, func_801CF348);
}

#include "overlays/plchar/PlChar_RunPersonalAction.h"

#include "overlays/plchar/PlChar_AdvancePaletteScript.h"

#include "overlays/plchar/PlChar_StartFacingScript.h"

#include "overlays/plchar/PlChar_ClearSlotRefIfUnused.h"

MATCH s32 func_801CEC28(s16 x, s16 y) {
    CHAR_PROBE_CELL_CODE(PlChar_SpawnLinkedActor);
}

/* func_801CEE34 */
#include "overlays/plchar/PlChar_SpawnLinkedActor.h"

MATCH void func_801CEF20(void) {
    SYS_DISPATCH_TASK(D_801D058C, 3, g_Task);
}

MATCH void func_801CEF64(void) {
    CHAR_START_FACING_TURN(func_801CF348);
}

#include "overlays/plchar/PlChar_ReleaseSpawnedActor.h"

#include "overlays/plchar/PlChar_ClearModeIfUnused.h"

#include "overlays/plchar/Char_ProbeFacingBlocked.h"
CHAR_DEFINE_PROBE_FACING_BLOCKED(func_801CF1A4);

MATCH void func_801CF348(void) {
    s16 dist;
    s32 x;
    s32 y;

    CHAR_PROBE_FACING_CLEARANCE(dist, x, y)
}

MATCH void func_801CF4AC(void) {
    SYS_DISPATCH_TASK(D_801D0598, 2, g_Task);
}

#include "overlays/plchar/PlChar_StartFacingTurn.h"

#include "overlays/plchar/PlChar_RunStepScriptRyuAdult.h"

MATCH void func_801CF6E0(void) {
    SYS_DISPATCH_TASK(D_801D05A4, 2, g_Task);
}

#include "overlays/plchar/PlChar_WalkStep.h"

#include "overlays/plchar/Char_RunFacingProbe.h"

MATCH void func_801CFA70(void){CHAR_RUN_FACING_PROBE()}
#include "overlays/plchar/PlChar_AdvanceScript.h"

#include "overlays/plchar/PlChar_ProbeCellSpawn.h"

#include "overlays/plchar/PlChar_SpawnActor.h"

#include "overlays/plchar/PlChar_ProbeFacingCell.h"

MATCH void func_801D0108(void) {
    SYS_DISPATCH_TASK(D_801D05B0, 2, g_Task);
}

#include "overlays/plchar/PlChar_StartTurnNinaAdult.h"

#include "overlays/plchar/PlChar_RunStepScriptNinaAdult.h"

MATCH void func_801D0314(void) {
    SYS_DISPATCH_TASK(D_801D05BC, 2, g_Task);
}

MATCH void func_801D0358(void) {
    u8 slot;

    if (!(g_Task->direction_08 & 1)) {
        g_Task->direction_08 = (g_Task->direction_08 - 1) & 7;
    }
    slot                     = func_8019601C();
    g_Task->param.actor_slot = slot;
    if (g_Task->param.actor_slot != GAME_NONE) {
        g_SpawnedActors[g_Task->param.actor_slot].header.flags = 1;
        g_SpawnedActors[g_Task->param.actor_slot].type         = 0x1B;
    }
    Actor_RequestScript((g_Task->direction_08 >> 1) + 0x42);
    /* FAKE: retail reads SND_PlayCue as void(s32). */
    ((void (*)(s32))SND_PlayCue)(g_Task->unk_2C + 0x100);
    g_Task->header.step++;
}

#include "overlays/plchar/PlChar_ClearModeIfSlotFree.h"

MATCH void func_801D04DC(void) {
    D_801D05C4[g_Task->unk_2C]();
}

MATCH void func_801D0520(void) {
    D_801D05D0[g_Task->unk_2C]();
}
