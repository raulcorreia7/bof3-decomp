#include "plp247_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/plchar/shared/PlChar_RunStepScript.h"

MATCH void func_801CEE08(void) {
    g_Game.current->u.field.mode.value = 0;
}

MATCH void func_801CEE18(void) {
    SYS_DISPATCH_TASK(D_801CFB1C, 2, g_Self);
}

#include "overlays/plchar/shared/PlChar_StartFacingTurn.h"

#include "overlays/plchar/shared/PlChar_RunStepScriptRyuAdult.h"

MATCH void func_801CF04C(void) {
    SYS_DISPATCH_TASK(D_801CFB28, 2, g_Self);
}

#include "overlays/plchar/shared/PlChar_WalkStep.h"

#include "overlays/plchar/shared/Char_RunFacingProbe.h"

MATCH void func_801CF3DC(void) {
    CHAR_RUN_FACING_PROBE()
}

#include "overlays/plchar/shared/PlChar_AdvanceScript.h"

#include "overlays/plchar/shared/PlChar_ProbeCellSpawn.h"
