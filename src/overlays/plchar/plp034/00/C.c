#include "plp034_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D02F4[((u8*)g_SpadWork)[2]]();
}

INCLUDE_ASM(func_801CE448);

#include "overlays/plchar/func_801CE628.h"

MATCH void func_801CE72C(void) {
    SYS_DISPATCH_TASK(D_801D0300, 2, g_SpadWork);
}

#include "overlays/plchar/func_801CE770.h"

INCLUDE_ASM(func_801CEA94);

#include "overlays/plchar/Char_AdvanceScript.h"

INCLUDE_ASM(func_801CED1C);

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801CF12C(void) {
    SYS_DISPATCH_TASK(D_801D030C, 2, g_SpadWork);
}

#include "overlays/plchar/Char_StartTurn.h"

MATCH void Char_RunStepScript_801CF23C(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_AWAY, CHARACTER_FACING_BACK);
}

MATCH void func_801CF338(void) {
    SYS_DISPATCH_TASK(D_801D0318, 2, g_SpadWork);
}

MATCH void func_801CF37C(void) {
    SYS_DISPATCH_TASK(D_801D0320, 3, g_SpadWork);
}

INCLUDE_ASM(func_801CF3C0);

INCLUDE_ASM(func_801CF4E0);

INCLUDE_ASM(func_801CF71C);

#include "overlays/plchar/Char_SelectScriptAndStep.h"

#include "overlays/plchar/Char_ClearSlotRefIfUnused.h"

INCLUDE_ASM(func_801CF940);

/* Char_SpawnActor variant (shared body in plchar/Char_SpawnActor.h, 57 instructions): this one adds 0x200 to the sampled
 * height and sets link_0B to 1, and keeps the args in $s2/$s3/$s4 with the constant in $s1; the template body with those two
 * edits and MATCH_REG pins still saves $s2 first where retail saves $s3 first (first difference at +0x4). */
INCLUDE_ASM(func_801CFB4C);

MATCH void func_801CFC38(void) {
    SYS_DISPATCH_TASK(D_801D0334, 3, g_SpadWork);
}

INCLUDE_ASM(func_801CFC7C);

INCLUDE_ASM(func_801CFCF4);

INCLUDE_ASM(func_801CFE14);

INCLUDE_ASM(func_801CFEAC);

MATCH void func_801D0050(void) {
    SYS_DISPATCH_TASK(D_801D0340, 2, g_SpadWork);
}

MATCH void Char_StartTurn_801D0094(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801D025C(void) {
    g_GameState->mode_12B.s8_value = 0;
}

MATCH void func_801D026C(void) {
    D_801D034C[g_SpadWork->unk_2C]();
}

MATCH void func_801D02B0(void) {
    D_801D0358[g_SpadWork->unk_2C]();
}
