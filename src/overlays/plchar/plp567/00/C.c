#include "plp567_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D078C[((u8*)g_SpadWork)[2]]();
}

MATCH void Char_StartTurn(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void Char_RunStepScript_801CE514(void) {
    CHAR_RUN_STEP_CASES(CHARACTER_FACING_AWAY, 0x41, CHARACTER_FACING_BACK, 0x40);
}

MATCH void func_801CE610(void) {
    SYS_DISPATCH_TASK(D_801D0798, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CE654);

#include "overlays/plchar/Char_ClaimLinkSlot.h"

#include "overlays/plchar/Char_PollScriptRequest.h"

MATCH void func_801CEA00(void) {
    SYS_DISPATCH_TASK(D_801D07A4, 2, g_SpadWork);
}

MATCH void Char_StartTurn_801CEA44(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CEC0C(void) {
    func_8014D978();
}

MATCH void func_801CEC2C(void) {
    SYS_DISPATCH_TASK(D_801D07B0, 2, g_SpadWork);
}

MATCH void func_801CEC70(void) {
    SYS_DISPATCH_TASK(D_801D07B8, 3, g_SpadWork);
}

INCLUDE_ASM(func_801CECB4);

INCLUDE_ASM(func_801CEDB4);

INCLUDE_ASM(func_801CF000);

#include "overlays/plchar/Char_SelectScriptAndStep.h"

#include "overlays/plchar/Char_ClearSlotRefIfUnused.h"

INCLUDE_ASM(func_801CF224);

/* Char_SpawnActor variant (shared body in plchar/Char_SpawnActor.h, 57 instructions): this one adds 0x200 to the sampled
 * height and sets link_0B to 1, and keeps the args in $s2/$s3/$s4 with the constant in $s1; the template body with those two
 * edits and MATCH_REG pins still saves $s2 first where retail saves $s3 first (first difference at +0x4). */
INCLUDE_ASM(func_801CF430);

MATCH void func_801CF51C(void) {
    SYS_DISPATCH_TASK(D_801D07CC, 3, g_SpadWork);
}

MATCH void func_801CF560(void) {
    func_801CF944();
    Actor_RequestScript((g_SpadWork->direction_08 - 1) / 2 + 0x42);
    g_SpadWork->unk_0A = 0xB;
    g_SpadWork->unk_03 = 1;
}

INCLUDE_ASM(func_801CF5CC);

MATCH void func_801CF704(void) {
    Actor* work = g_SpadWork;

    if ((g_ActorSlots[work->unk_0B].flags_00 == 0 || g_ActorSlots[work->unk_0B].unk_01 == 1) &&
        g_AreaCameraMoving == 0) {
        work->unk_2B                   = 0;
        g_GameState->mode_12B.s8_value = 0;
    }
    func_8014D978();
}

INCLUDE_ASM(func_801CF7A0);

INCLUDE_ASM(func_801CF944);

MATCH void func_801CFAA8(void) {
    SYS_DISPATCH_TASK(D_801D07D8, 2, g_SpadWork);
}

MATCH void func_801CFAEC(void) {
    s32 to_back;
    s32 to_away;

    if (g_SceneState.scenario_id == 15) {
        g_GameState->mode_12B.s8_value = 0;
    } else {
        to_back = g_SpadWork->direction_08 - 3;
        to_back = ABS(to_back);
        to_away = g_SpadWork->direction_08 - 5;
        to_away = ABS(to_away);
        if (to_away < to_back) {
            g_SpadWork->unk_0B = func_801B2D00(5);
            g_SpadWork->unk_03 = 5;
        } else {
            g_SpadWork->unk_0B = func_801B2D00(3);
            g_SpadWork->unk_03 = 3;
        }
        g_SpadWork->unk_09 = 2;
        g_SpadWork->state_02++;
    }
}

MATCH void Char_RunStepScript_801CFBE0(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void func_801CFCDC(void) {
    SYS_DISPATCH_TASK(D_801D07E4, 2, g_SpadWork);
}

#include "overlays/plchar/Char_WalkStep.h"

INCLUDE_ASM(func_801D006C);

#include "overlays/plchar/Char_AdvanceScript.h"

INCLUDE_ASM(func_801D02F4);

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801D0704(void) {
    D_801D07F0[g_SpadWork->unk_2C]();
}

MATCH void func_801D0748(void) {
    D_801D07FC[g_SpadWork->unk_2C]();
}
