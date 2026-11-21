#include "plp478_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CF6D8[g_Task->header.step]();
}

#include "overlays/plchar/shared/PlChar_StartTurn.h"

#include "overlays/plchar/shared/PlChar_RunStepScript.h"

MATCH void func_801CE610(void) {
    g_Game.current->u.field.mode.value = 0;
}

MATCH void func_801CE620(void) {
    SYS_DISPATCH_TASK(D_801CF6E4, 2, g_Task);
}

#include "overlays/plchar/shared/PlChar_StartFacingTurn.h"

#include "overlays/plchar/shared/PlChar_RunStepScriptRyuAdult.h"

MATCH void func_801CE854(void) {
    SYS_DISPATCH_TASK(D_801CF6F0, 2, g_Task);
}

#include "overlays/plchar/shared/PlChar_WalkStep.h"

#include "overlays/plchar/shared/Char_RunFacingProbe.h"

MATCH void func_801CEBE4(void){CHAR_RUN_FACING_PROBE()}
#include "overlays/plchar/shared/PlChar_AdvanceScript.h"

#include "overlays/plchar/shared/PlChar_ProbeCellSpawn.h"

#include "overlays/plchar/shared/PlChar_SpawnActor.h"

#include "overlays/plchar/shared/PlChar_ProbeFacingCell.h"

MATCH void func_801CF27C(void) {
    SYS_DISPATCH_TASK(D_801CF6FC, 2, g_Task);
}

#include "overlays/plchar/shared/PlChar_StartTurnNinaAdult.h"

#include "overlays/plchar/shared/PlChar_RunStepScriptNinaAdult.h"

MATCH void func_801CF488(void) {
    SYS_DISPATCH_TASK(D_801CF708, 2, g_Task);
}

#include "overlays/plchar/shared/PlChar_ClaimHelperSlotStep.h"

MATCH void func_801CF4CC(void) {
    PlChar_ClaimHelperSlotStep();
}

#include "overlays/plchar/shared/PlChar_ClearModeIfSlotFree.h"

MATCH void func_801CF650(void) {
    D_801CF710[g_Task->unk_2C]();
}

MATCH void func_801CF694(void) {
    D_801CF71C[g_Task->unk_2C]();
}
