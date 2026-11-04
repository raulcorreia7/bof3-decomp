#include "plp247_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CFAFC[((u8*)g_SpadWork)[2]]();
}

MATCH void Char_StartTurn_801CE448(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void Char_RunStepScript_801CE514(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_AWAY, CHARACTER_FACING_BACK);
}

MATCH void func_801CE610(void) {
    SYS_DISPATCH_TASK(D_801CFB08, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CE654);

#include "overlays/plchar/Char_TickPauseTimer.h"

INCLUDE_ASM(func_801CE8AC);

INCLUDE_ASM(func_801CEA10);

INCLUDE_ASM(func_801CEAE0);

MATCH void func_801CEBFC(void) {
    SYS_DISPATCH_TASK(D_801CFB10, 2, g_SpadWork);
}

MATCH void Char_StartTurn(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CEE08(void) {
    g_GameState->mode_12B.s8_value = 0;
}

MATCH void func_801CEE18(void) {
    SYS_DISPATCH_TASK(D_801CFB1C, 2, g_SpadWork);
}

#include "overlays/plchar/Char_StartFacingTurn.h"

MATCH void Char_RunStepScript_801CEF50(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void func_801CF04C(void) {
    SYS_DISPATCH_TASK(D_801CFB28, 2, g_SpadWork);
}

#include "overlays/plchar/Char_WalkStep.h"

INCLUDE_ASM(func_801CF3DC);

#include "overlays/plchar/Char_AdvanceScript.h"

INCLUDE_ASM(func_801CF664);

#include "overlays/plchar/Char_SpawnActor.h"

/* func_801CF940 */
#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801CFA74(void) {
    D_801CFB34[g_SpadWork->unk_2C]();
}

MATCH void func_801CFAB8(void) {
    D_801CFB40[g_SpadWork->unk_2C]();
}
