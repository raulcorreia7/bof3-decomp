#include "plp015_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CFB84[((u8*)g_SpadWork)[2]]();
}

INCLUDE_ASM(func_801CE448);

#include "overlays/plchar/func_801CE628.h"

MATCH void func_801CE72C(void) {
    SYS_DISPATCH_TASK(D_801CFB90, 2, g_SpadWork);
}

#include "overlays/plchar/func_801CE770.h"

INCLUDE_ASM(func_801CEA94);

#include "overlays/plchar/Char_AdvanceScript.h"

INCLUDE_ASM(func_801CED1C);

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801CF12C(void) {
    SYS_DISPATCH_TASK(D_801CFB9C, 2, g_SpadWork);
}

#include "overlays/plchar/Char_StartTurn.h"

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CF338(void) {
    SYS_DISPATCH_TASK(D_801CFBA8, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CF37C);

#include "overlays/plchar/Char_ClearModeIfSlotFree.h"

MATCH void func_801CF500(void) {
    SYS_DISPATCH_TASK(D_801CFBB0, 2, g_SpadWork);
}

/* This copy turns between facings 3 and 5; the image's own are the header's. */
MATCH void Char_StartTurn_801CF544(void) {
    CHAR_START_TURN(3, 5);
}

/* Runs one route step script: facing 5 requests script 0x41 and facing 3 requests 0x40,
 * the reverse of the script ids in CHAR_RUN_STEP_SCRIPT (plchar.h). */
#include "../../Char_AdvanceFacingTurn.h"

MATCH void func_801CF70C(void) {
    SYS_DISPATCH_TASK(D_801CFBBC, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CF750);

#include "overlays/plchar/Char_ClaimLinkSlot.h"

#include "overlays/plchar/Char_PollScriptRequest.h"

MATCH void func_801CFAFC(void) {
    D_801CFBC8[g_SpadWork->unk_2C]();
}

MATCH void func_801CFB40(void) {
    D_801CFBD4[g_SpadWork->unk_2C]();
}
