#include "plp467_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D03AC[g_Task->header.step]();
}

#include "overlays/plchar/shared/PlChar_StartTurn.h"

#include "overlays/plchar/shared/PlChar_RunStepScript.h"

MATCH void func_801CE610(void) {
    g_Game.current->u.field.mode.value = 0;
}

MATCH void func_801CE620(void) {
    SYS_DISPATCH_TASK(D_801D03B8, 2, g_Task);
}

#include "overlays/plchar/shared/PlChar_StartTurnPeco.h"

#include "overlays/plchar/shared/PlChar_RunStepScriptPeco.h"

MATCH void func_801CE82C(void) {
    Actor_StepAnimLoop();
}

MATCH void func_801CE84C(void) {
    SYS_DISPATCH_TASK(D_801D03C4, 2, g_Task);
}

MATCH void func_801CE890(void) {
    SYS_DISPATCH_TASK(D_801D03CC, 3, g_Task);
}

MATCH void PlChar_FaceFreeDirection(void) {
    CHAR_FACE_FREE_DIRECTION(func_801CF3C0, func_801CF564);
}

#include "overlays/plchar/shared/PlChar_RunPersonalAction.h"

#include "overlays/plchar/shared/PlChar_AdvancePaletteScript.h"

#include "overlays/plchar/shared/PlChar_StartFacingScript.h"

#include "overlays/plchar/shared/PlChar_ClearSlotRefIfUnused.h"

MATCH s32 func_801CEE44(s16 x, s16 y) {
    CHAR_PROBE_CELL_CODE(PlChar_SpawnLinkedActor);
}

/* func_801CF050 */
#include "overlays/plchar/shared/PlChar_SpawnLinkedActor.h"

MATCH void func_801CF13C(void) {
    SYS_DISPATCH_TASK(D_801D03E0, 3, g_Task);
}

MATCH void func_801CF180(void) {
    CHAR_START_FACING_TURN(func_801CF564);
}

#include "overlays/plchar/shared/PlChar_ReleaseSpawnedActor.h"

#include "overlays/plchar/shared/PlChar_ClearModeIfUnused.h"

#include "overlays/plchar/shared/Char_ProbeFacingBlocked.h"
CHAR_DEFINE_PROBE_FACING_BLOCKED(func_801CF3C0);

MATCH void func_801CF564(void) {
    s16 dist;
    s32 x;
    s32 y;

    CHAR_PROBE_FACING_CLEARANCE(dist, x, y)
}

MATCH void func_801CF6C8(void) {
    SYS_DISPATCH_TASK(D_801D03EC, 2, g_Task);
}

#include "overlays/plchar/shared/PlChar_StartFacingTurn.h"

#include "overlays/plchar/shared/PlChar_RunStepScriptRyuAdult.h"

MATCH void func_801CF8FC(void) {
    SYS_DISPATCH_TASK(D_801D03F8, 2, g_Task);
}

#include "overlays/plchar/shared/PlChar_WalkStep.h"

#include "overlays/plchar/shared/Char_RunFacingProbe.h"

MATCH void func_801CFC8C(void){CHAR_RUN_FACING_PROBE()}
#include "overlays/plchar/shared/PlChar_AdvanceScript.h"

#include "overlays/plchar/shared/PlChar_ProbeCellSpawn.h"

#include "overlays/plchar/shared/PlChar_SpawnActor.h"

#include "overlays/plchar/shared/PlChar_ProbeFacingCell.h"

MATCH void func_801D0324(void) {
    D_801D0404[g_Task->unk_2C]();
}

MATCH void func_801D0368(void) {
    D_801D0410[g_Task->unk_2C]();
}
