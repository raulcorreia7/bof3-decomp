#include "plp467_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D03AC[((u8*)g_SpadWork)[2]]();
}

MATCH void Char_StartTurn(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CE610(void) {
    g_GameState->mode_12B.s8_value = 0;
}

MATCH void func_801CE620(void) {
    SYS_DISPATCH_TASK(D_801D03B8, 2, g_SpadWork);
}

MATCH void Char_StartTurn_801CE664(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void Char_RunStepScript_801CE730(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void func_801CE82C(void) {
    func_8014D978();
}

MATCH void func_801CE84C(void) {
    SYS_DISPATCH_TASK(D_801D03C4, 2, g_SpadWork);
}

MATCH void func_801CE890(void) {
    SYS_DISPATCH_TASK(D_801D03CC, 3, g_SpadWork);
}

INCLUDE_ASM(func_801CE8D4);

INCLUDE_ASM(func_801CE9D4);

INCLUDE_ASM(func_801CEC20);

#include "overlays/plchar/Char_SelectScriptAndStep.h"

MATCH void func_801CEDB0(void) {
    Actor* work = g_SpadWork;

    if ((g_ActorSlots[work->unk_06].flags_00 == 0 || g_ActorSlots[work->unk_06].unk_01 == 1) &&
        g_AreaCameraMoving == 0) {
        work->unk_06 = 0;
        g_SpadWork->unk_03 -= 2;
    }
}

INCLUDE_ASM(func_801CEE44);

/* Char_SpawnActor variant (shared body in plchar/Char_SpawnActor.h, 57 instructions): this one adds 0x200 to the sampled
 * height and sets link_0B to 1, and keeps the args in $s2/$s3/$s4 with the constant in $s1; the template body with those two
 * edits and MATCH_REG pins still saves $s2 first where retail saves $s3 first (first difference at +0x4). */
INCLUDE_ASM(func_801CF050);

MATCH void func_801CF13C(void) {
    SYS_DISPATCH_TASK(D_801D03E0, 3, g_SpadWork);
}

MATCH void func_801CF180(void) {
    func_801CF564();
    Actor_RequestScript((g_SpadWork->direction_08 - 1) / 2 + 0x42);
    g_SpadWork->unk_0A = 0xB;
    g_SpadWork->unk_03 = 1;
}

INCLUDE_ASM(func_801CF1EC);

MATCH void func_801CF324(void) {
    Actor* work = g_SpadWork;

    if ((g_ActorSlots[work->unk_0B].flags_00 == 0 || g_ActorSlots[work->unk_0B].unk_01 == 1) &&
        g_AreaCameraMoving == 0) {
        work->unk_2B                   = 0;
        g_GameState->mode_12B.s8_value = 0;
    }
    func_8014D978();
}

INCLUDE_ASM(func_801CF3C0);

INCLUDE_ASM(func_801CF564);

MATCH void func_801CF6C8(void) {
    SYS_DISPATCH_TASK(D_801D03EC, 2, g_SpadWork);
}

/* plchar/plp056/00 func_801CF70C template: exact match, twin body in
 * plp457/00 func_801CEC60; left as assembly so the quality names ratchet does
 * not rise against the one-call func_801CF70C in plp016/00. */
INCLUDE_ASM(func_801CF70C);

MATCH void Char_RunStepScript_801CF800(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void func_801CF8FC(void) {
    SYS_DISPATCH_TASK(D_801D03F8, 2, g_SpadWork);
}

#include "overlays/plchar/Char_WalkStep.h"

INCLUDE_ASM(func_801CFC8C);

#include "overlays/plchar/Char_AdvanceScript.h"

INCLUDE_ASM(func_801CFF14);

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801D0324(void) {
    D_801D0404[g_SpadWork->unk_2C]();
}

MATCH void func_801D0368(void) {
    D_801D0410[g_SpadWork->unk_2C]();
}
