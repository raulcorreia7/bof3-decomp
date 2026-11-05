#include "plp016_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D0630[TASK_BYTES[2]]();
}

INCLUDE_ASM(func_801CE448);

#include "overlays/plchar/func_801CE628.h"

MATCH void func_801CE72C(void) {
    SYS_DISPATCH_TASK(D_801D063C, 2, g_Task);
}

#include "overlays/plchar/func_801CE770.h"

INCLUDE_ASM(func_801CEA94);

#include "overlays/plchar/Char_AdvanceScript.h"

INCLUDE_ASM(func_801CED1C);

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

INCLUDE_ASM(func_801CF37C);

#include "overlays/plchar/Char_ClearModeIfSlotFree.h"

MATCH void func_801CF500(void) {
    SYS_DISPATCH_TASK(D_801D065C, 2, g_Task);
}

/* This copy turns between facings 3 and 5; the image's own are the header's. */
MATCH void Char_StartTurn_801CF544(void) {
    CHAR_START_TURN(3, 5);
}

/* The second route step script in this image turns between directions 3 and 5. */
MATCH void Char_RunStepScript_801CF610(void) {
    CHAR_RUN_STEP_SCRIPT(3, 5);
}

MATCH void func_801CF70C(void) {
    func_8014D978();
}

MATCH void func_801CF72C(void) {
    SYS_DISPATCH_TASK(D_801D0668, 2, g_Task);
}

MATCH void func_801CF770(void) {
    SYS_DISPATCH_TASK(D_801D0670, 3, g_Task);
}

#include "overlays/plchar/Char_TurnAndRequestScript.h"

INCLUDE_ASM(func_801CF8B4);

#include "overlays/plchar/Char_AdvancePaletteScript.h"

#include "overlays/plchar/Char_SelectScriptAndStep.h"

#include "overlays/plchar/Char_ClearSlotRefIfUnused.h"

INCLUDE_ASM(func_801CFD24);

/* Exact draft: pin y to s4 and kind to s2, leave x unpinned; shared twins need an evidenced name. */
INCLUDE_ASM(func_801CFF30);

MATCH void func_801D001C(void) {
    SYS_DISPATCH_TASK(D_801D0684, 3, g_Task);
}

MATCH void func_801D0060(void) {
    func_801D0444();
    Actor_RequestScript((g_Task->direction_08 - 1) / 2 + 0x42);
    g_Task->unk_0A = 0xB;
    g_Task->unk_03 = 1;
}

INCLUDE_ASM(func_801D00CC);

#include "overlays/plchar/Char_ClearModeIfUnused.h"

INCLUDE_ASM(func_801D02A0);

INCLUDE_ASM(func_801D0444);

MATCH void func_801D05A8(void) {
    D_801D0690[g_Task->unk_2C]();
}

MATCH void func_801D05EC(void) {
    D_801D069C[g_Task->unk_2C]();
}
