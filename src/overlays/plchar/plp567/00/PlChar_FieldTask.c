#include "plp567_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D078C[g_Task->header.step]();
}

#include "overlays/plchar/shared/PlChar_StartTurn.h"

#include "overlays/plchar/shared/PlChar_RunStepScriptMomo.h"

MATCH void func_801CE610(void) {
    SYS_DISPATCH_TASK(D_801D0798, 2, g_Task);
}

MATCH void func_801CE654(void) {
    CHAR_START_FREE_FACING;
}

#include "overlays/plchar/shared/PlChar_ClaimLinkSlot.h"

#include "overlays/plchar/shared/PlChar_PollScriptRequest.h"

MATCH void func_801CEA00(void) {
    SYS_DISPATCH_TASK(D_801D07A4, 2, g_Task);
}

#include "overlays/plchar/shared/PlChar_StartTurnPeco.h"

#include "overlays/plchar/shared/PlChar_RunStepScript.h"

MATCH void func_801CEC0C(void) {
    Actor_StepAnimLoop();
}

MATCH void func_801CEC2C(void) {
    SYS_DISPATCH_TASK(D_801D07B0, 2, g_Task);
}

MATCH void func_801CEC70(void) {
    SYS_DISPATCH_TASK(D_801D07B8, 3, g_Task);
}

MATCH void PlChar_FaceFreeDirection(void) {
    CHAR_FACE_FREE_DIRECTION(func_801CF7A0, func_801CF944);
}

#include "overlays/plchar/shared/PlChar_RunPersonalAction.h"

#include "overlays/plchar/shared/PlChar_AdvancePaletteScript.h"

#include "overlays/plchar/shared/PlChar_StartFacingScript.h"

#include "overlays/plchar/shared/PlChar_ClearSlotRefIfUnused.h"

MATCH s32 func_801CF224(s16 x, s16 y) {
    CHAR_PROBE_CELL_CODE(PlChar_SpawnLinkedActor);
}

/* func_801CF430 */
#include "overlays/plchar/shared/PlChar_SpawnLinkedActor.h"

MATCH void func_801CF51C(void) {
    SYS_DISPATCH_TASK(D_801D07CC, 3, g_Task);
}

MATCH void func_801CF560(void) {
    CHAR_START_FACING_TURN(func_801CF944);
}

#include "overlays/plchar/shared/PlChar_ReleaseSpawnedActor.h"

#include "overlays/plchar/shared/PlChar_ClearModeIfUnused.h"

#include "overlays/plchar/shared/Char_ProbeFacingBlocked.h"
CHAR_DEFINE_PROBE_FACING_BLOCKED(func_801CF7A0);

MATCH void func_801CF944(void) {
    s16 dist;
    s32 x;
    s32 y;

    CHAR_PROBE_FACING_CLEARANCE(dist, x, y)
}

MATCH void func_801CFAA8(void) {
    SYS_DISPATCH_TASK(D_801D07D8, 2, g_Task);
}

#include "overlays/plchar/shared/PlChar_StartNearestFacingTurn.h"

#include "overlays/plchar/shared/PlChar_RunStepScriptRyuAdult.h"

MATCH void func_801CFCDC(void) {
    SYS_DISPATCH_TASK(D_801D07E4, 2, g_Task);
}

#include "overlays/plchar/shared/PlChar_WalkStep.h"

#include "overlays/plchar/shared/Char_RunFacingProbe.h"

MATCH void func_801D006C(void){CHAR_RUN_FACING_PROBE()}
#include "overlays/plchar/shared/PlChar_AdvanceScript.h"

#include "overlays/plchar/shared/PlChar_ProbeCellSpawn.h"

#include "overlays/plchar/shared/PlChar_SpawnActor.h"

#include "overlays/plchar/shared/PlChar_ProbeFacingCell.h"

MATCH void func_801D0704(void) {
    D_801D07F0[g_Task->unk_2C]();
}

MATCH void func_801D0748(void) {
    D_801D07FC[g_Task->unk_2C]();
}
