#include "plp026_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D0A54[g_Task->header.step]();
}

#include "overlays/plchar/func_801CE448.h"

#include "overlays/plchar/func_801CE628.h"

MATCH void func_801CE72C(void) {
    SYS_DISPATCH_TASK(D_801D0A60, 2, g_Task);
}

#include "overlays/plchar/func_801CE770.h"

#include "overlays/plchar/Char_RunFacingProbe.h"

MATCH void func_801CEA94(void){CHAR_RUN_FACING_PROBE()}
#include "overlays/plchar/PlChar_AdvanceScript.h"

#include "overlays/plchar/PlChar_ProbeCellSpawn.h"

#include "overlays/plchar/PlChar_SpawnActor.h"

#include "overlays/plchar/PlChar_ProbeFacingCell.h"

MATCH void func_801CF12C(void) {
    SYS_DISPATCH_TASK(D_801D0A6C, 2, g_Task);
}

#include "overlays/plchar/PlChar_StartTurn.h"

#include "overlays/plchar/PlChar_RunStepScriptGarr.h"

MATCH void func_801CF338(void) {
    SYS_DISPATCH_TASK(D_801D0A78, 2, g_Task);
}

/* func_801CF37C */
#include "overlays/plchar/PlChar_RunGarrFieldTask.h"

MATCH void PlChar_RunGarrFieldTask(void) {
    PLCHAR_RUN_GARR_FIELD_TASK(func_801CF808);
}

#include "overlays/plchar/func_801CF564.h"

/* func_801CF5D4 */
#include "overlays/plchar/PlChar_FindGarrActorSlot.h"

#include "overlays/plchar/PlChar_FollowerInReach.h"

#include "overlays/plchar/PlChar_ProbeFacingFollower.h"

MATCH void func_801CF924(void) {
    SYS_DISPATCH_TASK(D_801D0A80, 2, g_Task);
}

#include "overlays/plchar/PlChar_StartTurnPeco.h"

#include "overlays/plchar/PlChar_RunStepScript.h"

MATCH void func_801CFB30(void) {
    Actor_StepAnimLoop();
}

MATCH void func_801CFB50(void) {
    SYS_DISPATCH_TASK(D_801D0A8C, 2, g_Task);
}

MATCH void func_801CFB94(void) {
    SYS_DISPATCH_TASK(D_801D0A94, 3, g_Task);
}

MATCH void PlChar_FaceFreeDirection(void) {
    CHAR_FACE_FREE_DIRECTION(func_801D06C4, func_801D0868);
}

#include "overlays/plchar/PlChar_RunPersonalAction.h"

#include "overlays/plchar/PlChar_AdvancePaletteScript.h"

#include "overlays/plchar/PlChar_StartFacingScript.h"

#include "overlays/plchar/PlChar_ClearSlotRefIfUnused.h"

MATCH s32 func_801D0148(s16 x, s16 y) {
    CHAR_PROBE_CELL_CODE(PlChar_SpawnLinkedActor);
}

/* func_801D0354 */
#include "overlays/plchar/PlChar_SpawnLinkedActor.h"

MATCH void func_801D0440(void) {
    SYS_DISPATCH_TASK(D_801D0AA8, 3, g_Task);
}

MATCH void func_801D0484(void) {
    CHAR_START_FACING_TURN(func_801D0868);
}

#include "overlays/plchar/PlChar_ReleaseSpawnedActor.h"

#include "overlays/plchar/PlChar_ClearModeIfUnused.h"

#include "overlays/plchar/Char_ProbeFacingBlocked.h"
CHAR_DEFINE_PROBE_FACING_BLOCKED(func_801D06C4);

MATCH void func_801D0868(void) {
    s16 dist;
    s32 x;
    s32 y;

    CHAR_PROBE_FACING_CLEARANCE(dist, x, y)
}

MATCH void func_801D09CC(void) {
    D_801D0AB4[g_Task->unk_2C]();
}

MATCH void func_801D0A10(void) {
    D_801D0AC0[g_Task->unk_2C]();
}
