#include "plp026_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D0A54[SELF(Actor)->header.step]();
}

#include "overlays/plchar/shared/func_801CE448.h"

#include "overlays/plchar/shared/func_801CE628.h"

MATCH void func_801CE72C(void) {
    SYS_DISPATCH_TASK(D_801D0A60, 2, g_Self);
}

#include "overlays/plchar/shared/func_801CE770.h"

#include "overlays/plchar/shared/Char_RunFacingProbe.h"

MATCH void func_801CEA94(void){CHAR_RUN_FACING_PROBE()}
#include "overlays/plchar/shared/PlChar_AdvanceScript.h"

#include "overlays/plchar/shared/PlChar_ProbeCellSpawn.h"

#include "overlays/plchar/shared/PlChar_SpawnActor.h"

#include "overlays/plchar/shared/PlChar_ProbeFacingCell.h"

MATCH void func_801CF12C(void) {
    SYS_DISPATCH_TASK(D_801D0A6C, 2, g_Self);
}

#include "overlays/plchar/shared/PlChar_StartTurn.h"

#include "overlays/plchar/shared/PlChar_RunStepScriptGarr.h"

MATCH void func_801CF338(void) {
    SYS_DISPATCH_TASK(D_801D0A78, 2, g_Self);
}

/* func_801CF37C */
#include "overlays/plchar/shared/PlChar_RunGarrFieldTask.h"

MATCH void PlChar_RunGarrFieldTask(void) {
    PLCHAR_RUN_GARR_FIELD_TASK(func_801CF808);
}

#include "overlays/plchar/shared/PlChar_TickPauseTimer.h"

/* func_801CF5D4 */
#include "overlays/plchar/shared/PlChar_FindGarrActorSlot.h"

#include "overlays/plchar/shared/PlChar_FollowerInReach.h"

#include "overlays/plchar/shared/PlChar_ProbeFacingFollower.h"

MATCH void func_801CF924(void) {
    SYS_DISPATCH_TASK(D_801D0A80, 2, g_Self);
}

#include "overlays/plchar/shared/PlChar_StartTurnPeco.h"

#include "overlays/plchar/shared/PlChar_RunStepScript.h"
