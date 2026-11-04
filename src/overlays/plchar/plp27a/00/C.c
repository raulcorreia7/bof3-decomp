#include "plp27a_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CF900[((u8*)g_SpadWork)[2]]();
}

MATCH void Char_StartTurn(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void Char_RunStepScript_801CE514(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_AWAY, CHARACTER_FACING_BACK);
}

MATCH void func_801CE610(void) {
    SYS_DISPATCH_TASK(D_801CF90C, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CE654);

#include "overlays/plchar/Char_TickPauseTimer.h"

INCLUDE_ASM(func_801CE8AC);

INCLUDE_ASM(func_801CEA10);

INCLUDE_ASM(func_801CEAE0);

MATCH void func_801CEBFC(void) {
    SYS_DISPATCH_TASK(D_801CF914, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CEC40);

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CEE30(void) {
    SYS_DISPATCH_TASK(D_801CF920, 2, g_SpadWork);
}

#include "overlays/plchar/Char_WalkStep.h"

INCLUDE_ASM(func_801CF1C0);

#include "overlays/plchar/Char_AdvanceScript.h"

INCLUDE_ASM(func_801CF448);

#include "overlays/plchar/Char_SpawnActor.h"

/* func_801CF724 */
#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801CF858(void) {
    g_GameState->mode_12B.s8_value = 0;
}

MATCH void func_801CF868(void) {
    g_GameState->mode_12B.s8_value = 0;
}

MATCH void func_801CF878(void) {
    D_801CF92C[g_SpadWork->unk_2C]();
}

MATCH void func_801CF8BC(void) {
    D_801CF938[g_SpadWork->unk_2C]();
}
