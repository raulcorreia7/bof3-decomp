#include "plp257_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CFEDC[((u8*)g_SpadWork)[2]]();
}

MATCH void Char_StartTurn_801CE448(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void Char_RunStepScript_801CE514(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_AWAY, CHARACTER_FACING_BACK);
}

MATCH void func_801CE610(void) {
    SYS_DISPATCH_TASK(D_801CFEE8, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CE654);

#include "overlays/plchar/Char_TickPauseTimer.h"

INCLUDE_ASM(func_801CE8AC);

INCLUDE_ASM(func_801CEA10);

INCLUDE_ASM(func_801CEAE0);

MATCH void func_801CEBFC(void) {
    SYS_DISPATCH_TASK(D_801CFEF0, 2, g_SpadWork);
}

MATCH void Char_StartTurn(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

/* Runs one route step script: facing 5 requests script 0x41 and facing 3 requests 0x40,
 * the reverse of the script ids in CHAR_RUN_STEP_SCRIPT (plchar.h). */
#include "../../Char_AdvanceFacingTurn.h"

MATCH void func_801CEE08(void) {
    SYS_DISPATCH_TASK(D_801CFEFC, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CEE4C);

#include "overlays/plchar/Char_ClaimLinkSlot.h"

#include "overlays/plchar/Char_PollScriptRequest.h"

MATCH void func_801CF1F8(void) {
    SYS_DISPATCH_TASK(D_801CFF08, 2, g_SpadWork);
}

#include "../../Char_StartNearestFacingTurn.h"

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CF42C(void) {
    SYS_DISPATCH_TASK(D_801CFF14, 2, g_SpadWork);
}

#include "overlays/plchar/Char_WalkStep.h"

INCLUDE_ASM(func_801CF7BC);

#include "overlays/plchar/Char_AdvanceScript.h"

INCLUDE_ASM(func_801CFA44);

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801CFE54(void) {
    D_801CFF20[g_SpadWork->unk_2C]();
}

MATCH void func_801CFE98(void) {
    D_801CFF2C[g_SpadWork->unk_2C]();
}
