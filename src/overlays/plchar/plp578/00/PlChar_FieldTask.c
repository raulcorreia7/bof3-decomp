#include "plp578_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CFAB8[g_Task->header.step]();
}

#include "overlays/plchar/shared/PlChar_StartTurnMomo.h"

#include "overlays/plchar/shared/PlChar_RunStepScriptMomo.h"

MATCH void func_801CE610(void) {
    SYS_DISPATCH_TASK(D_801CFAC4, 2, g_Task);
}

MATCH void func_801CE654(void) {
    CHAR_START_FREE_FACING;
}

#include "overlays/plchar/shared/PlChar_ClaimLinkSlot.h"

#include "overlays/plchar/shared/PlChar_PollScriptRequest.h"

MATCH void func_801CEA00(void) {
    SYS_DISPATCH_TASK(D_801CFAD0, 2, g_Task);
}

#include "overlays/plchar/shared/PlChar_StartFacingTurn.h"

#include "overlays/plchar/shared/PlChar_RunStepScript.h"

MATCH void func_801CEC34(void) {
    SYS_DISPATCH_TASK(D_801CFADC, 2, g_Task);
}

#include "overlays/plchar/shared/PlChar_WalkStep.h"

#include "overlays/plchar/shared/Char_RunFacingProbe.h"

MATCH void func_801CEFC4(void){CHAR_RUN_FACING_PROBE()}
#include "overlays/plchar/shared/PlChar_AdvanceScript.h"

#include "overlays/plchar/shared/PlChar_ProbeCellSpawn.h"

#include "overlays/plchar/shared/PlChar_SpawnActor.h"

#include "overlays/plchar/shared/PlChar_ProbeFacingCell.h"

MATCH void func_801CF65C(void) {
    SYS_DISPATCH_TASK(D_801CFAE8, 2, g_Task);
}

#include "overlays/plchar/shared/PlChar_StartTurn.h"

#include "overlays/plchar/shared/PlChar_RunStepScriptNinaAdult.h"

MATCH void func_801CF868(void) {
    SYS_DISPATCH_TASK(D_801CFAF4, 2, g_Task);
}

MATCH void func_801CF8AC(void) {
    u8 slot;

    if (!(g_Task->direction & 1)) {
        g_Task->direction = (g_Task->direction - 1) & 7;
    }
    slot                     = func_8019601C();
    g_Task->param.actor_slot = slot;
    if (g_Task->param.actor_slot != GAME_NONE) {
        g_SpawnedActors[g_Task->param.actor_slot].header.flags = 1;
        g_SpawnedActors[g_Task->param.actor_slot].type         = 0x1B;
    }
    Actor_RequestScript((g_Task->direction >> 1) + 0x42);
    /* FAKE: retail reads SND_PlaySE as void(s32). */
    ((void (*)(s32))SND_PlaySE)(g_Task->unk_2C + 0x100);
    g_Task->header.step++;
}

#include "overlays/plchar/shared/PlChar_ClearModeIfSlotFree.h"

MATCH void func_801CFA30(void) {
    D_801CFAFC[g_Task->unk_2C]();
}

MATCH void func_801CFA74(void) {
    D_801CFB08[g_Task->unk_2C]();
}
