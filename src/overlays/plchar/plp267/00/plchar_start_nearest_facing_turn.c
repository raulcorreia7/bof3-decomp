#include "plp267_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/plchar/shared/PlChar_StartNearestFacingTurn.h"

#include "overlays/plchar/shared/PlChar_RunStepScriptRyuAdult.h"

MATCH void func_801CFED8(void) {
    SYS_DISPATCH_TASK(D_801D09DC, 2, g_Self);
}

#include "overlays/plchar/shared/PlChar_WalkStep.h"

#include "overlays/plchar/shared/Char_RunFacingProbe.h"

MATCH void func_801D0268(void) {
    CHAR_RUN_FACING_PROBE()
}

#include "overlays/plchar/shared/PlChar_AdvanceScript.h"

#include "overlays/plchar/shared/PlChar_ProbeCellSpawn.h"
