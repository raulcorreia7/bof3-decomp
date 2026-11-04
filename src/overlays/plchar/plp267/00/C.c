#include "plp267_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D0988[((u8*)g_SpadWork)[2]]();
}

MATCH void Char_StartTurn_801CE448(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void Char_RunStepScript_801CE514(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_AWAY, CHARACTER_FACING_BACK);
}

MATCH void func_801CE610(void) {
    SYS_DISPATCH_TASK(D_801D0994, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CE654);

INCLUDE_ASM(func_801CE83C);

INCLUDE_ASM(func_801CE8AC);

INCLUDE_ASM(func_801CEA10);

INCLUDE_ASM(func_801CEAE0);

MATCH void func_801CEBFC(void) {
    SYS_DISPATCH_TASK(D_801D099C, 2, g_SpadWork);
}

MATCH void Char_StartTurn(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CEE08(void) {
    func_8014D978();
}

MATCH void func_801CEE28(void) {
    SYS_DISPATCH_TASK(D_801D09A8, 2, g_SpadWork);
}

MATCH void func_801CEE6C(void) {
    SYS_DISPATCH_TASK(D_801D09B0, 3, g_SpadWork);
}

INCLUDE_ASM(func_801CEEB0);

INCLUDE_ASM(func_801CEFB0);

INCLUDE_ASM(func_801CF1FC);

#include "overlays/plchar/Char_SelectScriptAndStep.h"

INCLUDE_ASM(func_801CF38C);

INCLUDE_ASM(func_801CF420);

/* Char_SpawnActor variant (shared body in plchar/Char_SpawnActor.h, 57 instructions): this one adds 0x200 to the sampled
 * height and sets link_0B to 1, and keeps the args in $s2/$s3/$s4 with the constant in $s1; the template body with those two
 * edits and MATCH_REG pins still saves $s2 first where retail saves $s3 first (first difference at +0x4). */
INCLUDE_ASM(func_801CF62C);

MATCH void func_801CF718(void) {
    SYS_DISPATCH_TASK(D_801D09C4, 3, g_SpadWork);
}

INCLUDE_ASM(func_801CF75C);

INCLUDE_ASM(func_801CF7C8);

INCLUDE_ASM(func_801CF900);

INCLUDE_ASM(func_801CF99C);

INCLUDE_ASM(func_801CFB40);

MATCH void func_801CFCA4(void) {
    SYS_DISPATCH_TASK(D_801D09D0, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CFCE8);

MATCH void Char_RunStepScript_801CFDDC(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void func_801CFED8(void) {
    SYS_DISPATCH_TASK(D_801D09DC, 2, g_SpadWork);
}

#include "overlays/plchar/Char_WalkStep.h"

INCLUDE_ASM(func_801D0268);

#include "overlays/plchar/Char_AdvanceScript.h"

INCLUDE_ASM(func_801D04F0);

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801D0900(void) {
    D_801D09E8[g_SpadWork->unk_2C]();
}

MATCH void func_801D0944(void) {
    D_801D09F4[g_SpadWork->unk_2C]();
}
