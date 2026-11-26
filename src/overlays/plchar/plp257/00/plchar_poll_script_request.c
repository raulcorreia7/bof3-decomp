#include "plp257_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/plchar/shared/PlChar_PollScriptRequest.h"

MATCH void func_801CF1F8(void) {
    SYS_DISPATCH_TASK(D_801CFF08, 2, g_Self);
}

#include "overlays/plchar/shared/PlChar_StartNearestFacingTurn.h"

#include "overlays/plchar/shared/PlChar_RunStepScript.h"

MATCH void func_801CF42C(void) {
    SYS_DISPATCH_TASK(D_801CFF14, 2, g_Self);
}

#include "overlays/plchar/shared/PlChar_WalkStep.h"

#include "overlays/plchar/shared/Char_RunFacingProbe.h"

MATCH void func_801CF7BC(void) {
    CHAR_RUN_FACING_PROBE()
}

#include "overlays/plchar/shared/PlChar_AdvanceScript.h"

#include "overlays/plchar/shared/PlChar_ProbeCellSpawn.h"
