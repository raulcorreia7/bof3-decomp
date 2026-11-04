#include "plp578_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CFAB8[((u8*)g_SpadWork)[2]]();
}

MATCH void Char_StartTurn_801CE448(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void Char_RunStepScript_801CE514(void) {
    CHAR_RUN_STEP_CASES(CHARACTER_FACING_AWAY, 0x41, CHARACTER_FACING_BACK, 0x40);
}

MATCH void func_801CE610(void) {
    SYS_DISPATCH_TASK(D_801CFAC4, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CE654);

INCLUDE_ASM(func_801CE820);

INCLUDE_ASM(func_801CE92C);

MATCH void func_801CEA00(void) {
    SYS_DISPATCH_TASK(D_801CFAD0, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CEA44);

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CEC34(void) {
    SYS_DISPATCH_TASK(D_801CFADC, 2, g_SpadWork);
}

#include "overlays/plchar/Char_WalkStep.h"

INCLUDE_ASM(func_801CEFC4);

#include "overlays/plchar/Char_AdvanceScript.h"

INCLUDE_ASM(func_801CF24C);

#include "overlays/plchar/Char_SpawnActor.h"

/* func_801CF528 */
#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801CF65C(void) {
    SYS_DISPATCH_TASK(D_801CFAE8, 2, g_SpadWork);
}

MATCH void Char_StartTurn(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void Char_RunStepScript_801CF76C(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_AWAY, CHARACTER_FACING_BACK);
}

MATCH void func_801CF868(void) {
    SYS_DISPATCH_TASK(D_801CFAF4, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CF8AC);

INCLUDE_ASM(func_801CF9C4);

MATCH void func_801CFA30(void) {
    D_801CFAFC[g_SpadWork->unk_2C]();
}

MATCH void func_801CFA74(void) {
    D_801CFB08[g_SpadWork->unk_2C]();
}
