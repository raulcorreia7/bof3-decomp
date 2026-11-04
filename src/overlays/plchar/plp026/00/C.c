#include "plp026_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D0A54[((u8*)g_SpadWork)[2]]();
}

INCLUDE_ASM(func_801CE448);

#include "overlays/plchar/func_801CE628.h"

MATCH void func_801CE72C(void) {
    SYS_DISPATCH_TASK(D_801D0A60, 2, g_SpadWork);
}

#include "overlays/plchar/func_801CE770.h"

INCLUDE_ASM(func_801CEA94);

#include "overlays/plchar/Char_AdvanceScript.h"

INCLUDE_ASM(func_801CED1C);

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801CF12C(void) {
    SYS_DISPATCH_TASK(D_801D0A6C, 2, g_SpadWork);
}

#include "overlays/plchar/Char_StartTurn.h"

MATCH void Char_RunStepScript_801CF23C(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_AWAY, CHARACTER_FACING_BACK);
}

MATCH void func_801CF338(void) {
    SYS_DISPATCH_TASK(D_801D0A78, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CF37C);

MATCH void func_801CF564(void) {
    if (g_SpadWork->unk_09 == 0) {
        g_GameState->mode_12B.s8_value = 0;
        g_GameFlags &= ~0x1000;
    } else {
        g_SpadWork->unk_09--;
        func_801B0DFC();
    }
    func_8014D978();
}

INCLUDE_ASM(func_801CF5D4);

INCLUDE_ASM(func_801CF738);

INCLUDE_ASM(func_801CF808);

MATCH void func_801CF924(void) {
    SYS_DISPATCH_TASK(D_801D0A80, 2, g_SpadWork);
}

MATCH void Char_StartTurn_801CF968(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CFB30(void) {
    func_8014D978();
}

MATCH void func_801CFB50(void) {
    SYS_DISPATCH_TASK(D_801D0A8C, 2, g_SpadWork);
}

MATCH void func_801CFB94(void) {
    SYS_DISPATCH_TASK(D_801D0A94, 3, g_SpadWork);
}

INCLUDE_ASM(func_801CFBD8);

INCLUDE_ASM(func_801CFCD8);

INCLUDE_ASM(func_801CFF24);

#include "overlays/plchar/Char_SelectScriptAndStep.h"

MATCH void func_801D00B4(void) {
    Actor* work = g_SpadWork;

    if ((g_ActorSlots[work->unk_06].flags_00 == 0 || g_ActorSlots[work->unk_06].unk_01 == 1) &&
        g_AreaCameraMoving == 0) {
        work->unk_06 = 0;
        g_SpadWork->unk_03 -= 2;
    }
}

INCLUDE_ASM(func_801D0148);

/* Char_SpawnActor variant (shared body in plchar/Char_SpawnActor.h, 57 instructions): this one adds 0x200 to the sampled
 * height and sets link_0B to 1, and keeps the args in $s2/$s3/$s4 with the constant in $s1; the template body with those two
 * edits and MATCH_REG pins still saves $s2 first where retail saves $s3 first (first difference at +0x4). */
INCLUDE_ASM(func_801D0354);

MATCH void func_801D0440(void) {
    SYS_DISPATCH_TASK(D_801D0AA8, 3, g_SpadWork);
}

INCLUDE_ASM(func_801D0484);

INCLUDE_ASM(func_801D04F0);

MATCH void func_801D0628(void) {
    Actor* work = g_SpadWork;

    if ((g_ActorSlots[work->unk_0B].flags_00 == 0 || g_ActorSlots[work->unk_0B].unk_01 == 1) &&
        g_AreaCameraMoving == 0) {
        work->unk_2B                   = 0;
        g_GameState->mode_12B.s8_value = 0;
    }
    func_8014D978();
}

INCLUDE_ASM(func_801D06C4);

INCLUDE_ASM(func_801D0868);

MATCH void func_801D09CC(void) {
    D_801D0AB4[g_SpadWork->unk_2C]();
}

MATCH void func_801D0A10(void) {
    D_801D0AC0[g_SpadWork->unk_2C]();
}
