#include "plp012_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/plchar/shared/PlChar_RunStepScriptGarr.h"

MATCH void func_801CF70C(void) {
    SYS_DISPATCH_TASK(D_801CFDB8, 2, g_Self);
}

/* func_801CF750 */
#include "overlays/plchar/shared/PlChar_RunGarrFieldTask.h"

MATCH void PlChar_RunGarrFieldTask(void) {
    PLCHAR_RUN_GARR_FIELD_TASK(func_801CFBDC);
}

/* func_801CF938 */
#include "overlays/plchar/shared/PlChar_TickPauseTimer.h"

/* func_801CF9A8 */
#include "overlays/plchar/shared/PlChar_FindGarrActorSlot.h"

/* func_801CFB0C */
#include "overlays/plchar/shared/PlChar_FollowerInReach.h"

#include "overlays/plchar/shared/PlChar_ProbeFacingFollower.h"

MATCH void func_801CFCF8(void) {
    D_801CFDC0[SELF(Actor)->unk_2C]();
}

MATCH void func_801CFD3C(void) {
    D_801CFDCC[SELF(Actor)->unk_2C]();
}
