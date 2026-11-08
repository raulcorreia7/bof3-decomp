#include "plp678_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D0564[TASK_BYTES[2]]();
}

MATCH void Char_StartTurn(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

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

INCLUDE_ASM(func_801CE6B8);

INCLUDE_ASM(func_801CE7B8);

#include "overlays/plchar/Char_AdvancePaletteScript.h"

#include "overlays/plchar/Char_StartFacingScript.h"

#include "overlays/plchar/Char_ClearSlotRefIfUnused.h"

/* hint: the work-pointer store of the 2 and 1 results shares one tail with the result held in v0 (g_Task loaded before the li in the jump delay slot); every C form folds the constant into each branch. The body is 4 bytes over. */
INCLUDE_ASM(func_801CEC28);

INCLUDE_ASM(func_801CEE34);

MATCH void func_801CEF20(void) {
    SYS_DISPATCH_TASK(D_801D058C, 3, g_Task);
}

MATCH void func_801CEF64(void) {
    func_801CF348();
    Actor_RequestScript((g_Task->direction_08 - 1) / 2 + 0x42);
    g_Task->unk_0A = 0xB;
    g_Task->unk_03 = 1;
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

MATCH void Char_RunStepScriptRyuAdult(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

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

MATCH void Char_StartTurnNinaAdult(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void Char_RunStepScriptNinaAdult(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_AWAY, CHARACTER_FACING_BACK);
}

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
