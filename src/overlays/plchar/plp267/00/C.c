#include "plp267_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D0988[TASK_BYTES[2]]();
}

MATCH void Char_StartTurn_801CE448(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void Char_RunStepScript_801CE514(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_AWAY, CHARACTER_FACING_BACK);
}

MATCH void func_801CE610(void) {
    SYS_DISPATCH_TASK(D_801D0994, 2, g_Task);
}

INCLUDE_ASM(func_801CE654);

#include "overlays/plchar/Char_TickPauseTimer.h"

INCLUDE_ASM(func_801CE8AC);

INCLUDE_ASM(func_801CEA10);

INCLUDE_ASM(func_801CEAE0);

MATCH void func_801CEBFC(void) {
    SYS_DISPATCH_TASK(D_801D099C, 2, g_Task);
}

MATCH void Char_StartTurn(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CEE08(void) {
    func_8014D978();
}

MATCH void func_801CEE28(void) {
    SYS_DISPATCH_TASK(D_801D09A8, 2, g_Task);
}

MATCH void func_801CEE6C(void) {
    SYS_DISPATCH_TASK(D_801D09B0, 3, g_Task);
}

#include "overlays/plchar/Char_FaceFreeDirection.h"

INCLUDE_ASM(func_801CEFB0);

#include "overlays/plchar/Char_AdvancePaletteScript.h"

#include "overlays/plchar/Char_StartFacingScript.h"

#include "overlays/plchar/Char_ClearSlotRefIfUnused.h"

MATCH s32 func_801CF420(s16 x, s16 y) {
    CHAR_PROBE_CELL_CODE(func_801CF62C);
}

/* blocker: save order; first diff: +0x4 s2 saved first (retail saves s3 first). */
INCLUDE_ASM(func_801CF62C);

MATCH void func_801CF718(void) {
    SYS_DISPATCH_TASK(D_801D09C4, 3, g_Task);
}

MATCH void func_801CF75C(void) {
    func_801CFB40();
    Actor_RequestScript((g_Task->direction_08 - 1) / 2 + 0x42);
    g_Task->unk_0A = 0xB;
    g_Task->unk_03 = 1;
}

INCLUDE_ASM(func_801CF7C8);

#include "overlays/plchar/Char_ClearModeIfUnused.h"

INCLUDE_ASM(func_801CF99C);

INCLUDE_ASM(func_801CFB40);

MATCH void func_801CFCA4(void) {
    SYS_DISPATCH_TASK(D_801D09D0, 2, g_Task);
}

#include "../../Char_StartNearestFacingTurn.h"

MATCH void Char_RunStepScript_801CFDDC(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void func_801CFED8(void) {
    SYS_DISPATCH_TASK(D_801D09DC, 2, g_Task);
}

#include "overlays/plchar/Char_WalkStep.h"

INCLUDE_ASM(func_801D0268);

#include "overlays/plchar/Char_AdvanceScript.h"

INCLUDE_ASM(func_801D04F0);

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801D0900(void) {
    D_801D09E8[g_Task->unk_2C]();
}

MATCH void func_801D0944(void) {
    D_801D09F4[g_Task->unk_2C]();
}
