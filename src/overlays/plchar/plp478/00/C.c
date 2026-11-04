#include "plp478_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CF6D8[((u8*)g_SpadWork)[2]]();
}

MATCH void Char_StartTurn(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CE610(void) {
    g_GameState->mode_12B.s8_value = 0;
}

MATCH void func_801CE620(void) {
    SYS_DISPATCH_TASK(D_801CF6E4, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CE664);

MATCH void Char_RunStepScript_801CE758(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void func_801CE854(void) {
    SYS_DISPATCH_TASK(D_801CF6F0, 2, g_SpadWork);
}

#include "overlays/plchar/Char_WalkStep.h"

INCLUDE_ASM(func_801CEBE4);

#include "overlays/plchar/Char_AdvanceScript.h"

INCLUDE_ASM(func_801CEE6C);

#include "overlays/plchar/Char_SpawnActor.h"

/* func_801CF148 */
#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801CF27C(void) {
    SYS_DISPATCH_TASK(D_801CF6FC, 2, g_SpadWork);
}

MATCH void Char_StartTurn_801CF2C0(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void Char_RunStepScript_801CF38C(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_AWAY, CHARACTER_FACING_BACK);
}

MATCH void func_801CF488(void) {
    SYS_DISPATCH_TASK(D_801CF708, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CF4CC);

#include "overlays/plchar/Char_ClearModeIfSlotFree.h"

MATCH void func_801CF650(void) {
    D_801CF710[g_SpadWork->unk_2C]();
}

MATCH void func_801CF694(void) {
    D_801CF71C[g_SpadWork->unk_2C]();
}
