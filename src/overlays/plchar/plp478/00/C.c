#include "plp478_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CF6D8[g_Task->header.step]();
}

#include "overlays/plchar/Char_StartTurn.h"

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CE610(void) {
    g_Game.current->u.field.mode_12B.s8_value = 0;
}

MATCH void func_801CE620(void) {
    SYS_DISPATCH_TASK(D_801CF6E4, 2, g_Task);
}

#include "overlays/plchar/Char_StartFacingTurn.h"

#include "overlays/plchar/Char_RunStepScriptRyuAdult.h"

MATCH void func_801CE854(void) {
    SYS_DISPATCH_TASK(D_801CF6F0, 2, g_Task);
}

#include "overlays/plchar/Char_WalkStep.h"

INCLUDE_ASM(func_801CEBE4);

#include "overlays/plchar/Char_AdvanceScript.h"

#include "overlays/plchar/Char_ProbeCellSpawn.h"

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801CF27C(void) {
    SYS_DISPATCH_TASK(D_801CF6FC, 2, g_Task);
}

#include "overlays/plchar/Char_StartTurnNinaAdult.h"

#include "overlays/plchar/Char_RunStepScriptNinaAdult.h"

MATCH void func_801CF488(void) {
    SYS_DISPATCH_TASK(D_801CF708, 2, g_Task);
}

#include "overlays/plchar/Char_ClaimHelperSlotStep.h"

MATCH void func_801CF4CC(void) {
    Char_ClaimHelperSlotStep();
}

#include "overlays/plchar/Char_ClearModeIfSlotFree.h"

MATCH void func_801CF650(void) {
    D_801CF710[g_Task->unk_2C]();
}

MATCH void func_801CF694(void) {
    D_801CF71C[g_Task->unk_2C]();
}
