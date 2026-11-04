#include "plp457_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CF900[((u8*)g_SpadWork)[2]]();
}

MATCH void Char_StartTurn(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CE610(void) {
    g_GameState->mode_12B.s8_value = 0;
}

MATCH void func_801CE620(void) {
    SYS_DISPATCH_TASK(D_801CF90C, 2, g_SpadWork);
}

MATCH void Char_StartTurn_801CE664(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

/* Follows CHAR_RUN_STEP_SCRIPT (plchar.h), but retail branches on the second
 * facing with `bne` and the 0x41 load in the delay slot, where the macro emits
 * `beq`; the script selection needs another switch or if form. */
MATCH void Char_RunStepScript_801CE730(void) {
    CHAR_RUN_STEP_CASES(CHARACTER_FACING_AWAY, 0x41, CHARACTER_FACING_BACK, 0x40);
}

MATCH void func_801CE82C(void) {
    SYS_DISPATCH_TASK(D_801CF918, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CE870);

INCLUDE_ASM(func_801CEA3C);

#include "overlays/plchar/Char_PollScriptRequest.h"

MATCH void func_801CEC1C(void) {
    SYS_DISPATCH_TASK(D_801CF924, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CEC60);

MATCH void Char_RunStepScript_801CED54(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void func_801CEE50(void) {
    SYS_DISPATCH_TASK(D_801CF930, 2, g_SpadWork);
}

#include "overlays/plchar/Char_WalkStep.h"

INCLUDE_ASM(func_801CF1E0);

#include "overlays/plchar/Char_AdvanceScript.h"

INCLUDE_ASM(func_801CF468);

#include "overlays/plchar/Char_SpawnActor.h"

/* func_801CF744 */
#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801CF878(void) {
    D_801CF93C[g_SpadWork->unk_2C]();
}

MATCH void func_801CF8BC(void) {
    D_801CF948[g_SpadWork->unk_2C]();
}
