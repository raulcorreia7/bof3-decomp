#include "plp278_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CFCB4[g_Task->header.step]();
}

#include "overlays/plchar/shared/PlChar_StartTurnGarr.h"

#include "overlays/plchar/shared/PlChar_RunStepScriptGarr.h"

MATCH void func_801CE610(void) {
    SYS_DISPATCH_TASK(D_801CFCC0, 2, g_Task);
}

/* func_801CE654 */
#include "overlays/plchar/shared/PlChar_RunGarrFieldTask.h"

MATCH void PlChar_RunGarrFieldTask(void) {
    PLCHAR_RUN_GARR_FIELD_TASK(func_801CEAE0);
}

#include "overlays/plchar/shared/PlChar_TickPauseTimer.h"

/* func_801CE8AC */
#include "overlays/plchar/shared/PlChar_FindGarrActorSlot.h"

#include "overlays/plchar/shared/PlChar_FollowerInReach.h"

#include "overlays/plchar/shared/PlChar_ProbeFacingFollower.h"

MATCH void func_801CEBFC(void) {
    SYS_DISPATCH_TASK(D_801CFCC8, 2, g_Task);
}

#include "overlays/plchar/shared/PlChar_StartFacingTurn.h"

#include "overlays/plchar/shared/PlChar_RunStepScript.h"

MATCH void func_801CEE30(void) {
    SYS_DISPATCH_TASK(D_801CFCD4, 2, g_Task);
}

#include "overlays/plchar/shared/PlChar_WalkStep.h"

#include "overlays/plchar/shared/Char_RunFacingProbe.h"

MATCH void func_801CF1C0(void){CHAR_RUN_FACING_PROBE()}
#include "overlays/plchar/shared/PlChar_AdvanceScript.h"

#include "overlays/plchar/shared/PlChar_ProbeCellSpawn.h"

#include "overlays/plchar/shared/PlChar_SpawnActor.h"

#include "overlays/plchar/shared/PlChar_ProbeFacingCell.h"

MATCH void func_801CF858(void) {
    SYS_DISPATCH_TASK(D_801CFCE0, 2, g_Task);
}

#include "overlays/plchar/shared/PlChar_StartTurn.h"

#include "overlays/plchar/shared/PlChar_RunStepScriptNinaAdult.h"

MATCH void func_801CFA64(void) {
    SYS_DISPATCH_TASK(D_801CFCEC, 2, g_Task);
}

#include "overlays/plchar/shared/PlChar_ClaimHelperSlotStep.h"

MATCH void func_801CFAA8(void) {
    PlChar_ClaimHelperSlotStep();
}

#include "overlays/plchar/shared/PlChar_ClearModeIfSlotFree.h"

MATCH void func_801CFC2C(void) {
    D_801CFCF4[g_Task->unk_2C]();
}

MATCH void func_801CFC70(void) {
    D_801CFD00[g_Task->unk_2C]();
}
