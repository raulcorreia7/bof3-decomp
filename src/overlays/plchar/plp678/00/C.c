#include "plp678_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D0564[g_Task->header.step]();
}

#include "overlays/plchar/Char_StartTurn.h"

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CE610(void) {
    func_8014D978();
}

MATCH void func_801CE630(void) {
    SYS_DISPATCH_TASK(D_801D0570, 2, g_Task);
}

MATCH void func_801CE674(void) {
    SYS_DISPATCH_TASK(D_801D0578, 3, g_Task);
}

/* func_801CE6B8 */
MATCH void Char_FaceFreeDirection(void) {
    CHAR_FACE_FREE_DIRECTION(func_801CF1A4, func_801CF348);
}

INCLUDE_ASM(func_801CE7B8);

#include "overlays/plchar/Char_AdvancePaletteScript.h"

#include "overlays/plchar/Char_StartFacingScript.h"

#include "overlays/plchar/Char_ClearSlotRefIfUnused.h"

MATCH s32 func_801CEC28(s16 x, s16 y) {
    CHAR_PROBE_CELL_CODE(func_801CEE34);
}

INCLUDE_ASM(func_801CEE34);

MATCH void func_801CEF20(void) {
    SYS_DISPATCH_TASK(D_801D058C, 3, g_Task);
}

MATCH void func_801CEF64(void) {
    CHAR_START_FACING_TURN(func_801CF348);
}

INCLUDE_ASM(func_801CEFD0);

#include "overlays/plchar/Char_ClearModeIfUnused.h"

/* blocker: probe flag register; first diff: +0x3C addu s2,a0,v0 (retail cx in s1, cy in s0, the flag computed in v0 and moved to s2 in the delay slot) against cx in s2 and the flag in s0 (candidate); body is Char_ProbeFacingCell with the cell test 0xF0/0xF1/0xF4/0xF6/0xF7 plus func_801B5AE4 != -1. */
INCLUDE_ASM(func_801CF1A4);

INCLUDE_ASM(func_801CF348);

MATCH void func_801CF4AC(void) {
    SYS_DISPATCH_TASK(D_801D0598, 2, g_Task);
}

#include "overlays/plchar/Char_StartFacingTurn.h"

#include "overlays/plchar/Char_RunStepScriptRyuAdult.h"

MATCH void func_801CF6E0(void) {
    SYS_DISPATCH_TASK(D_801D05A4, 2, g_Task);
}

#include "overlays/plchar/Char_WalkStep.h"

INCLUDE_ASM(func_801CFA70);

#include "overlays/plchar/Char_AdvanceScript.h"

#include "overlays/plchar/Char_ProbeCellSpawn.h"

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801D0108(void) {
    SYS_DISPATCH_TASK(D_801D05B0, 2, g_Task);
}

#include "overlays/plchar/Char_StartTurnNinaAdult.h"

#include "overlays/plchar/Char_RunStepScriptNinaAdult.h"

MATCH void func_801D0314(void) {
    SYS_DISPATCH_TASK(D_801D05BC, 2, g_Task);
}

INCLUDE_ASM(func_801D0358);

#include "overlays/plchar/Char_ClearModeIfSlotFree.h"

MATCH void func_801D04DC(void) {
    D_801D05C4[g_Task->unk_2C]();
}

MATCH void func_801D0520(void) {
    D_801D05D0[g_Task->unk_2C]();
}
