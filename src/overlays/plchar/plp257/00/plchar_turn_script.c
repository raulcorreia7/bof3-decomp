#include "plp257_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CFEDC[SELF(Actor)->header.step]();
}

#include "overlays/plchar/shared/PlChar_StartTurnGarr.h"

#include "overlays/plchar/shared/PlChar_RunStepScriptGarr.h"

MATCH void func_801CE610(void) {
    SYS_DISPATCH_TASK(D_801CFEE8, 2, g_Self);
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
    SYS_DISPATCH_TASK(D_801CFEF0, 2, g_Self);
}

#include "overlays/plchar/shared/PlChar_StartTurn.h"
