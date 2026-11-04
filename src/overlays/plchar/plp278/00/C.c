#include "plp278_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CFCB4[((u8*)g_SpadWork)[2]]();
}

MATCH void Char_StartTurn_801CE448(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void Char_RunStepScript_801CE514(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_AWAY, CHARACTER_FACING_BACK);
}

MATCH void func_801CE610(void) {
    SYS_DISPATCH_TASK(D_801CFCC0, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CE654);

#include "overlays/plchar/Char_TickPauseTimer.h"

INCLUDE_ASM(func_801CE8AC);

INCLUDE_ASM(func_801CEA10);

INCLUDE_ASM(func_801CEAE0);

MATCH void func_801CEBFC(void) {
    SYS_DISPATCH_TASK(D_801CFCC8, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CEC40);

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CEE30(void) {
    SYS_DISPATCH_TASK(D_801CFCD4, 2, g_SpadWork);
}

#include "overlays/plchar/Char_WalkStep.h"

INCLUDE_ASM(func_801CF1C0);

#include "overlays/plchar/Char_AdvanceScript.h"

INCLUDE_ASM(func_801CF448);

#include "overlays/plchar/Char_SpawnActor.h"

/* func_801CF724 */
#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801CF858(void) {
    SYS_DISPATCH_TASK(D_801CFCE0, 2, g_SpadWork);
}

MATCH void Char_StartTurn(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void Char_RunStepScript_801CF968(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_AWAY, CHARACTER_FACING_BACK);
}

MATCH void func_801CFA64(void) {
    SYS_DISPATCH_TASK(D_801CFCEC, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CFAA8);

#include "overlays/plchar/Char_ClearModeIfSlotFree.h"

MATCH void func_801CFC2C(void) {
    D_801CFCF4[g_SpadWork->unk_2C]();
}

MATCH void func_801CFC70(void) {
    D_801CFD00[g_SpadWork->unk_2C]();
}
