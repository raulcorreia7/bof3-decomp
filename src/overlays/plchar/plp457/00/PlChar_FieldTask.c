#include "plp457_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CF900[g_Task->header.step]();
}

#include "overlays/plchar/PlChar_StartTurn.h"

#include "overlays/plchar/PlChar_RunStepScript.h"

MATCH void func_801CE610(void) {
    g_Game.current->u.field.mode_12B.s8_value = 0;
}

MATCH void func_801CE620(void) {
    SYS_DISPATCH_TASK(D_801CF90C, 2, g_Task);
}

#include "overlays/plchar/PlChar_StartTurnMomo.h"

#include "overlays/plchar/PlChar_RunStepScriptMomo.h"

MATCH void func_801CE82C(void) {
    SYS_DISPATCH_TASK(D_801CF918, 2, g_Task);
}

MATCH void func_801CE870(void) {
    CHAR_START_FREE_FACING;
}

#include "overlays/plchar/PlChar_ClaimLinkSlot.h"

#include "overlays/plchar/PlChar_PollScriptRequest.h"

MATCH void func_801CEC1C(void) {
    SYS_DISPATCH_TASK(D_801CF924, 2, g_Task);
}

#include "overlays/plchar/PlChar_StartNearestFacingTurn.h"

#include "overlays/plchar/PlChar_RunStepScriptRyuAdult.h"

MATCH void func_801CEE50(void) {
    SYS_DISPATCH_TASK(D_801CF930, 2, g_Task);
}

#include "overlays/plchar/PlChar_WalkStep.h"

#include "overlays/plchar/Char_RunFacingProbe.h"

MATCH void func_801CF1E0(void){CHAR_RUN_FACING_PROBE()}
#include "overlays/plchar/PlChar_AdvanceScript.h"

#include "overlays/plchar/PlChar_ProbeCellSpawn.h"

#include "overlays/plchar/PlChar_SpawnActor.h"

#include "overlays/plchar/PlChar_ProbeFacingCell.h"

MATCH void func_801CF878(void) {
    D_801CF93C[g_Task->unk_2C]();
}

MATCH void func_801CF8BC(void) {
    D_801CF948[g_Task->unk_2C]();
}
