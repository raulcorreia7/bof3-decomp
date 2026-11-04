#include "plp678_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D0564[((u8*)g_SpadWork)[2]]();
}

MATCH void Char_StartTurn(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CE610(void) {
    func_8014D978();
}

MATCH void func_801CE630(void) {
    SYS_DISPATCH_TASK(D_801D0570, 2, g_SpadWork);
}

MATCH void func_801CE674(void) {
    SYS_DISPATCH_TASK(D_801D0578, 3, g_SpadWork);
}

INCLUDE_ASM(func_801CE6B8);

INCLUDE_ASM(func_801CE7B8);

INCLUDE_ASM(func_801CEA04);

#include "overlays/plchar/Char_SelectScriptAndStep.h"

MATCH void func_801CEB94(void) {
    Actor* work = g_SpadWork;

    if ((g_ActorSlots[work->unk_06].flags_00 == 0 || g_ActorSlots[work->unk_06].unk_01 == 1) &&
        g_AreaCameraMoving == 0) {
        work->unk_06 = 0;
        g_SpadWork->unk_03 -= 2;
    }
}

INCLUDE_ASM(func_801CEC28);

INCLUDE_ASM(func_801CEE34);

MATCH void func_801CEF20(void) {
    SYS_DISPATCH_TASK(D_801D058C, 3, g_SpadWork);
}

INCLUDE_ASM(func_801CEF64);

INCLUDE_ASM(func_801CEFD0);

MATCH void func_801CF108(void) {
    Actor* work = g_SpadWork;

    if ((g_ActorSlots[work->unk_0B].flags_00 == 0 || g_ActorSlots[work->unk_0B].unk_01 == 1) &&
        g_AreaCameraMoving == 0) {
        work->unk_2B                   = 0;
        g_GameState->mode_12B.s8_value = 0;
    }
    func_8014D978();
}

INCLUDE_ASM(func_801CF1A4);

INCLUDE_ASM(func_801CF348);

MATCH void func_801CF4AC(void) {
    SYS_DISPATCH_TASK(D_801D0598, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CF4F0);

MATCH void Char_RunStepScript_801CF5E4(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void func_801CF6E0(void) {
    SYS_DISPATCH_TASK(D_801D05A4, 2, g_SpadWork);
}

#include "overlays/plchar/Char_WalkStep.h"

INCLUDE_ASM(func_801CFA70);

#include "overlays/plchar/Char_AdvanceScript.h"

INCLUDE_ASM(func_801CFCF8);

#include "overlays/plchar/Char_SpawnActor.h"

/* func_801CFFD4 */
#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801D0108(void) {
    SYS_DISPATCH_TASK(D_801D05B0, 2, g_SpadWork);
}

MATCH void Char_StartTurn_801D014C(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void Char_RunStepScript_801D0218(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_AWAY, CHARACTER_FACING_BACK);
}

MATCH void func_801D0314(void) {
    SYS_DISPATCH_TASK(D_801D05BC, 2, g_SpadWork);
}

INCLUDE_ASM(func_801D0358);

#include "overlays/plchar/Char_ClearModeIfSlotFree.h"

MATCH void func_801D04DC(void) {
    D_801D05C4[g_SpadWork->unk_2C]();
}

MATCH void func_801D0520(void) {
    D_801D05D0[g_SpadWork->unk_2C]();
}
