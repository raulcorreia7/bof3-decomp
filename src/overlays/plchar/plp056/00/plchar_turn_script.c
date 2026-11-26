#include "plp056_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D0858[SELF(Actor)->header.step]();
}

#include "overlays/plchar/shared/func_801CE448.h"

#include "overlays/plchar/shared/func_801CE628.h"

MATCH void func_801CE72C(void) {
    SYS_DISPATCH_TASK(D_801D0864, 2, g_Self);
}

#include "overlays/plchar/shared/func_801CE770.h"

#include "overlays/plchar/shared/Char_RunFacingProbe.h"

MATCH void func_801CEA94(void){CHAR_RUN_FACING_PROBE()}
#include "overlays/plchar/shared/PlChar_AdvanceScript.h"

#include "overlays/plchar/shared/PlChar_ProbeCellSpawn.h"

#include "overlays/plchar/shared/PlChar_SpawnActor.h"

#include "overlays/plchar/shared/PlChar_ProbeFacingCell.h"

MATCH void func_801CF12C(void) {
    SYS_DISPATCH_TASK(D_801D0870, 2, g_Self);
}

#include "overlays/plchar/shared/PlChar_StartTurn.h"

/* Runs one route step script: facing 5 requests script 0x41 and facing 3 requests 0x40,
 * the reverse of the script ids in CHAR_RUN_STEP_SCRIPT (plchar.h). */
#include "overlays/plchar/shared/PlChar_AdvanceFacingTurn.h"
