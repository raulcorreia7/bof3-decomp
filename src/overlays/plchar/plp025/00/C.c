#include "plp025_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CFFA8[g_Task->header.step]();
}

#include "overlays/plchar/func_801CE448.h"

#include "overlays/plchar/func_801CE628.h"

MATCH void func_801CE72C(void) {
    SYS_DISPATCH_TASK(D_801CFFB4, 2, g_Task);
}

#include "overlays/plchar/func_801CE770.h"

INCLUDE_ASM(func_801CEA94);

#include "overlays/plchar/Char_AdvanceScript.h"

#include "overlays/plchar/Char_ProbeCellSpawn.h"

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801CF12C(void) {
    SYS_DISPATCH_TASK(D_801CFFC0, 2, g_Task);
}

#include "overlays/plchar/Char_StartTurn.h"

MATCH void Char_RunStepScript(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_AWAY, CHARACTER_FACING_BACK);
}

MATCH void func_801CF338(void) {
    SYS_DISPATCH_TASK(D_801CFFCC, 2, g_Task);
}

/* func_801CF37C */
#include "overlays/plchar/PlChar_RunGarrFieldTask.h"

MATCH void PlChar_RunGarrFieldTask(void) {
    PLCHAR_RUN_GARR_FIELD_TASK(func_801CF808);
}

#include "overlays/plchar/func_801CF564.h"

/* func_801CF5D4 */
#include "overlays/plchar/PlChar_FindGarrActorSlot.h"

/* func_801CF738 */
#include "overlays/plchar/PlChar_FollowerInReach.h"

#include "overlays/plchar/PlChar_ProbeFacingFollower.h"

MATCH void func_801CF924(void) {
    SYS_DISPATCH_TASK(D_801CFFD4, 2, g_Task);
}

#include "overlays/plchar/Char_StartTurnMomo.h"

/* Runs one route step script: facing 5 requests script 0x41 and facing 3 requests 0x40,
 * the reverse of the script ids in CHAR_RUN_STEP_SCRIPT (plchar.h). */
#include "overlays/plchar/Char_AdvanceFacingTurn.h"

MATCH void func_801CFB30(void) {
    SYS_DISPATCH_TASK(D_801CFFE0, 2, g_Task);
}

INCLUDE_ASM(func_801CFB74);

#include "overlays/plchar/Char_ClaimLinkSlot.h"

#include "overlays/plchar/Char_PollScriptRequest.h"

MATCH void func_801CFF20(void) {
    D_801CFFEC[g_Task->unk_2C]();
}

MATCH void func_801CFF64(void) {
    D_801CFFF8[g_Task->unk_2C]();
}
