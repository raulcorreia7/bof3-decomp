#include "plp457_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/plchar/shared/PlChar_PollScriptRequest.h"

MATCH void func_801CEC1C(void) {
    SYS_DISPATCH_TASK(D_801CF924, 2, g_Self);
}

#include "overlays/plchar/shared/PlChar_StartNearestFacingTurn.h"

#include "overlays/plchar/shared/PlChar_RunStepScriptRyuAdult.h"

MATCH void func_801CEE50(void) {
    SYS_DISPATCH_TASK(D_801CF930, 2, g_Self);
}

#include "overlays/plchar/shared/PlChar_WalkStep.h"

#include "overlays/plchar/shared/Char_RunFacingProbe.h"

MATCH void func_801CF1E0(void) {
    CHAR_RUN_FACING_PROBE()
}

#include "overlays/plchar/shared/PlChar_AdvanceScript.h"

#include "overlays/plchar/shared/PlChar_ProbeCellSpawn.h"
