#include "plp578_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/plchar/shared/PlChar_PollScriptRequest.h"

MATCH void func_801CEA00(void) {
    SYS_DISPATCH_TASK(D_801CFAD0, 2, g_Self);
}

#include "overlays/plchar/shared/PlChar_StartFacingTurn.h"

#include "overlays/plchar/shared/PlChar_RunStepScript.h"

MATCH void func_801CEC34(void) {
    SYS_DISPATCH_TASK(D_801CFADC, 2, g_Self);
}

#include "overlays/plchar/shared/PlChar_WalkStep.h"

#include "overlays/plchar/shared/Char_RunFacingProbe.h"

MATCH void func_801CEFC4(void) {
    CHAR_RUN_FACING_PROBE()
}

#include "overlays/plchar/shared/PlChar_AdvanceScript.h"

#include "overlays/plchar/shared/PlChar_ProbeCellSpawn.h"
