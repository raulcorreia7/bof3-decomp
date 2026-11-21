#include "plp267_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D0988[g_Task->header.step]();
}

#include "overlays/plchar/shared/PlChar_StartTurnGarr.h"

#include "overlays/plchar/shared/PlChar_RunStepScriptGarr.h"

MATCH void func_801CE610(void) {
    SYS_DISPATCH_TASK(D_801D0994, 2, g_Task);
}

/* func_801CE654 */
#include "overlays/plchar/shared/PlChar_RunGarrFieldTask.h"

MATCH void PlChar_RunGarrFieldTask(void) {
    PLCHAR_RUN_GARR_FIELD_TASK(func_801CEAE0);
}

#include "overlays/plchar/shared/PlChar_TickPauseTimer.h"

/* func_801CE8AC */
#include "overlays/plchar/shared/PlChar_FindGarrActorSlot.h"

#include "overlays/plchar/shared/PlChar_FollowerInReach.h"

#include "overlays/plchar/shared/PlChar_ProbeFacingFollower.h"

MATCH void func_801CEBFC(void) {
    SYS_DISPATCH_TASK(D_801D099C, 2, g_Task);
}

#include "overlays/plchar/shared/PlChar_StartTurn.h"

#include "overlays/plchar/shared/PlChar_RunStepScript.h"

MATCH void func_801CEE08(void) {
    Actor_StepAnimLoop();
}

MATCH void func_801CEE28(void) {
    SYS_DISPATCH_TASK(D_801D09A8, 2, g_Task);
}

MATCH void func_801CEE6C(void) {
    SYS_DISPATCH_TASK(D_801D09B0, 3, g_Task);
}

MATCH void PlChar_FaceFreeDirection(void) {
    CHAR_FACE_FREE_DIRECTION(func_801CF99C, PlChar_ProbeFacingClearance);
}

#include "overlays/plchar/shared/PlChar_RunPersonalAction.h"

#include "overlays/plchar/shared/PlChar_AdvancePaletteScript.h"

#include "overlays/plchar/shared/PlChar_StartFacingScript.h"

#include "overlays/plchar/shared/PlChar_ClearSlotRefIfUnused.h"

MATCH s32 func_801CF420(s16 x, s16 y) {
    CHAR_PROBE_CELL_CODE(PlChar_SpawnLinkedActor);
}

/* func_801CF62C */
#include "overlays/plchar/shared/PlChar_SpawnLinkedActor.h"

MATCH void func_801CF718(void) {
    SYS_DISPATCH_TASK(D_801D09C4, 3, g_Task);
}

MATCH void func_801CF75C(void) {
    CHAR_START_FACING_TURN(PlChar_ProbeFacingClearance);
}

#include "overlays/plchar/shared/PlChar_ReleaseSpawnedActor.h"

#include "overlays/plchar/shared/PlChar_ClearModeIfUnused.h"

#include "overlays/plchar/shared/Char_ProbeFacingBlocked.h"
CHAR_DEFINE_PROBE_FACING_BLOCKED(func_801CF99C);

/* func_801CFB40 */
#include "overlays/plchar/shared/PlChar_ProbeFacingClearance.h"

MATCH void func_801CFCA4(void) {
    SYS_DISPATCH_TASK(D_801D09D0, 2, g_Task);
}

#include "overlays/plchar/shared/PlChar_StartNearestFacingTurn.h"

#include "overlays/plchar/shared/PlChar_RunStepScriptRyuAdult.h"

MATCH void func_801CFED8(void) {
    SYS_DISPATCH_TASK(D_801D09DC, 2, g_Task);
}

#include "overlays/plchar/shared/PlChar_WalkStep.h"

#include "overlays/plchar/shared/Char_RunFacingProbe.h"

MATCH void func_801D0268(void){CHAR_RUN_FACING_PROBE()}
#include "overlays/plchar/shared/PlChar_AdvanceScript.h"

#include "overlays/plchar/shared/PlChar_ProbeCellSpawn.h"

#include "overlays/plchar/shared/PlChar_SpawnActor.h"

#include "overlays/plchar/shared/PlChar_ProbeFacingCell.h"

MATCH void func_801D0900(void) {
    D_801D09E8[g_Task->unk_2C]();
}

MATCH void func_801D0944(void) {
    D_801D09F4[g_Task->unk_2C]();
}
