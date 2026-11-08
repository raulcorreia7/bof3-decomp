#include "plp467_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D03AC[TASK_BYTES[2]]();
}

MATCH void Char_StartTurn(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CE610(void) {
    g_Game.current->u.field.mode_12B.s8_value = 0;
}

MATCH void func_801CE620(void) {
    SYS_DISPATCH_TASK(D_801D03B8, 2, g_Task);
}

MATCH void Char_StartTurnPeco(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void Char_RunStepScriptPeco(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void func_801CE82C(void) {
    func_8014D978();
}

MATCH void func_801CE84C(void) {
    SYS_DISPATCH_TASK(D_801D03C4, 2, g_Task);
}

MATCH void func_801CE890(void) {
    SYS_DISPATCH_TASK(D_801D03CC, 3, g_Task);
}

#include "overlays/plchar/Char_FaceFreeDirection.h"

INCLUDE_ASM(func_801CE9D4);

#include "overlays/plchar/Char_AdvancePaletteScript.h"

#include "overlays/plchar/Char_StartFacingScript.h"

#include "overlays/plchar/Char_ClearSlotRefIfUnused.h"

MATCH s32 func_801CEE44(s16 x, s16 y) {
    CHAR_PROBE_CELL_CODE(func_801CF050);
}

/* blocker: save order; first diff: +0x4 s2 saved first (retail saves s3 first). */
INCLUDE_ASM(func_801CF050);

MATCH void func_801CF13C(void) {
    SYS_DISPATCH_TASK(D_801D03E0, 3, g_Task);
}

MATCH void func_801CF180(void) {
    func_801CF564();
    Actor_RequestScript((g_Task->direction_08 - 1) / 2 + 0x42);
    g_Task->unk_0A = 0xB;
    g_Task->unk_03 = 1;
}

INCLUDE_ASM(func_801CF1EC);

#include "overlays/plchar/Char_ClearModeIfUnused.h"

INCLUDE_ASM(func_801CF3C0);

INCLUDE_ASM(func_801CF564);

MATCH void func_801CF6C8(void) {
    SYS_DISPATCH_TASK(D_801D03EC, 2, g_Task);
}

#include "overlays/plchar/Char_StartFacingTurn.h"

MATCH void Char_RunStepScriptRyuAdult(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void func_801CF8FC(void) {
    SYS_DISPATCH_TASK(D_801D03F8, 2, g_Task);
}

#include "overlays/plchar/Char_WalkStep.h"

INCLUDE_ASM(func_801CFC8C);

#include "overlays/plchar/Char_AdvanceScript.h"

#include "overlays/plchar/Char_ProbeCellSpawn.h"

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801D0324(void) {
    D_801D0404[g_Task->unk_2C]();
}

MATCH void func_801D0368(void) {
    D_801D0410[g_Task->unk_2C]();
}
