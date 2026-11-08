#include "plp026_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D0A54[TASK_BYTES[2]]();
}

INCLUDE_ASM(func_801CE448);

#include "overlays/plchar/func_801CE628.h"

MATCH void func_801CE72C(void) {
    SYS_DISPATCH_TASK(D_801D0A60, 2, g_Task);
}

#include "overlays/plchar/func_801CE770.h"

INCLUDE_ASM(func_801CEA94);

#include "overlays/plchar/Char_AdvanceScript.h"

#include "overlays/plchar/Char_ProbeCellSpawn.h"

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801CF12C(void) {
    SYS_DISPATCH_TASK(D_801D0A6C, 2, g_Task);
}

#include "overlays/plchar/Char_StartTurn.h"

#include "overlays/plchar/Char_RunStepScriptGarr.h"

MATCH void func_801CF338(void) {
    SYS_DISPATCH_TASK(D_801D0A78, 2, g_Task);
}

INCLUDE_ASM(func_801CF37C);

#include "overlays/plchar/func_801CF564.h"

INCLUDE_ASM(func_801CF5D4);

INCLUDE_ASM(func_801CF738);

INCLUDE_ASM(func_801CF808);

MATCH void func_801CF924(void) {
    SYS_DISPATCH_TASK(D_801D0A80, 2, g_Task);
}

#include "overlays/plchar/Char_StartTurnPeco.h"

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CFB30(void) {
    func_8014D978();
}

MATCH void func_801CFB50(void) {
    SYS_DISPATCH_TASK(D_801D0A8C, 2, g_Task);
}

MATCH void func_801CFB94(void) {
    SYS_DISPATCH_TASK(D_801D0A94, 3, g_Task);
}

#include "overlays/plchar/Char_FaceFreeDirection.h"

INCLUDE_ASM(func_801CFCD8);

#include "overlays/plchar/Char_AdvancePaletteScript.h"

#include "overlays/plchar/Char_StartFacingScript.h"

#include "overlays/plchar/Char_ClearSlotRefIfUnused.h"

MATCH s32 func_801D0148(s16 x, s16 y) {
    CHAR_PROBE_CELL_CODE(func_801D0354);
}

/* blocker: save order; first diff: +0x4 s2 saved first (retail saves s3 first). */
INCLUDE_ASM(func_801D0354);

MATCH void func_801D0440(void) {
    SYS_DISPATCH_TASK(D_801D0AA8, 3, g_Task);
}

/* func_801D0484 */
MATCH void PlChar_RequestFacingScript(void) {
    func_801D0868();
    Actor_RequestScript((g_Task->direction_08 - 1) / 2 + 0x42);
    g_Task->unk_0A = 0xB;
    g_Task->unk_03 = 1;
}

INCLUDE_ASM(func_801D04F0);

#include "overlays/plchar/Char_ClearModeIfUnused.h"

INCLUDE_ASM(func_801D06C4);

INCLUDE_ASM(func_801D0868);

MATCH void func_801D09CC(void) {
    D_801D0AB4[g_Task->unk_2C]();
}

MATCH void func_801D0A10(void) {
    D_801D0AC0[g_Task->unk_2C]();
}
