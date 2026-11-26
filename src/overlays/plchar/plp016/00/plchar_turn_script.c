#include "plp016_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D0630[SELF(Actor)->header.step]();
}

#include "overlays/plchar/shared/func_801CE448.h"

#include "overlays/plchar/shared/func_801CE628.h"

MATCH void func_801CE72C(void) {
    SYS_DISPATCH_TASK(D_801D063C, 2, g_Self);
}

#include "overlays/plchar/shared/func_801CE770.h"

#include "overlays/plchar/shared/Char_RunFacingProbe.h"

MATCH void func_801CEA94(void){CHAR_RUN_FACING_PROBE()}
#include "overlays/plchar/shared/PlChar_AdvanceScript.h"

#include "overlays/plchar/shared/PlChar_ProbeCellSpawn.h"

#include "overlays/plchar/shared/PlChar_SpawnActor.h"

#include "overlays/plchar/shared/PlChar_ProbeFacingCell.h"

MATCH void func_801CF12C(void) {
    SYS_DISPATCH_TASK(D_801D0648, 2, g_Self);
}

#include "overlays/plchar/shared/PlChar_StartTurn.h"

#include "overlays/plchar/shared/PlChar_RunStepScript.h"

MATCH void func_801CF338(void) {
    SYS_DISPATCH_TASK(D_801D0654, 2, g_Self);
}

#include "overlays/plchar/shared/PlChar_ClaimHelperSlotStep.h"

MATCH void func_801CF37C(void) {
    PlChar_ClaimHelperSlotStep();
}

#include "overlays/plchar/shared/PlChar_ClearModeIfSlotFree.h"

MATCH void func_801CF500(void) {
    SYS_DISPATCH_TASK(D_801D065C, 2, g_Self);
}

#include "overlays/plchar/shared/PlChar_StartTurnPeco.h"
