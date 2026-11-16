#include "plp016_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D0630[g_Task->header.step]();
}

#include "overlays/plchar/func_801CE448.h"

#include "overlays/plchar/func_801CE628.h"

MATCH void func_801CE72C(void) {
    SYS_DISPATCH_TASK(D_801D063C, 2, g_Task);
}

#include "overlays/plchar/func_801CE770.h"

#include "overlays/plchar/Char_RunFacingProbe.h"

MATCH void func_801CEA94(void){CHAR_RUN_FACING_PROBE()}
#include "overlays/plchar/Char_AdvanceScript.h"

#include "overlays/plchar/Char_ProbeCellSpawn.h"

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801CF12C(void) {
    SYS_DISPATCH_TASK(D_801D0648, 2, g_Task);
}

#include "overlays/plchar/Char_StartTurn.h"

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CF338(void) {
    SYS_DISPATCH_TASK(D_801D0654, 2, g_Task);
}

#include "overlays/plchar/Char_ClaimHelperSlotStep.h"

MATCH void func_801CF37C(void) {
    Char_ClaimHelperSlotStep();
}

#include "overlays/plchar/Char_ClearModeIfSlotFree.h"

MATCH void func_801CF500(void) {
    SYS_DISPATCH_TASK(D_801D065C, 2, g_Task);
}

#include "overlays/plchar/Char_StartTurnPeco.h"

#include "overlays/plchar/Char_RunStepScriptPeco.h"

MATCH void func_801CF70C(void) {
    Actor_StepAnimLoop();
}

MATCH void func_801CF72C(void) {
    SYS_DISPATCH_TASK(D_801D0668, 2, g_Task);
}

MATCH void func_801CF770(void) {
    SYS_DISPATCH_TASK(D_801D0670, 3, g_Task);
}

MATCH void Char_FaceFreeDirection(void) {
    CHAR_FACE_FREE_DIRECTION(func_801D02A0, func_801D0444);
}

#include "overlays/plchar/Char_RunPersonalAction.h"

#include "overlays/plchar/Char_AdvancePaletteScript.h"

#include "overlays/plchar/Char_StartFacingScript.h"

#include "overlays/plchar/Char_ClearSlotRefIfUnused.h"

MATCH s32 func_801CFD24(s16 x, s16 y) {
    CHAR_PROBE_CELL_CODE(Char_SpawnLinkedActor);
}

/* func_801CFF30 */
#include "overlays/plchar/Char_SpawnLinkedActor.h"

MATCH void func_801D001C(void) {
    SYS_DISPATCH_TASK(D_801D0684, 3, g_Task);
}

MATCH void func_801D0060(void) {
    CHAR_START_FACING_TURN(func_801D0444);
}

#include "overlays/plchar/Char_ReleaseSpawnedActor.h"

#include "overlays/plchar/Char_ClearModeIfUnused.h"

#include "overlays/plchar/Char_ProbeFacingBlocked.h"
CHAR_DEFINE_PROBE_FACING_BLOCKED(func_801D02A0);

MATCH void func_801D0444(void) {
    s16 dist;
    s32 x;
    s32 y;

    CHAR_PROBE_FACING_CLEARANCE(dist, x, y)
}

MATCH void func_801D05A8(void) {
    D_801D0690[g_Task->unk_2C]();
}

MATCH void func_801D05EC(void) {
    D_801D069C[g_Task->unk_2C]();
}
