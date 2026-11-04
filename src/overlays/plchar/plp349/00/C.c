#include "plp349_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CF5EC[((u8*)g_SpadWork)[2]]();
}

MATCH void Char_StartTurn_801CE448(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

MATCH void Char_RunStepScript_801CE514(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_AWAY, CHARACTER_FACING_BACK);
}

MATCH void func_801CE610(void) {
    SYS_DISPATCH_TASK(D_801CF5F8, 2, g_SpadWork);
}

MATCH void func_801CE654(void) {
    SYS_DISPATCH_TASK(D_801CF600, 3, g_SpadWork);
}

INCLUDE_ASM(func_801CE698);

INCLUDE_ASM(func_801CE7B8);

INCLUDE_ASM(func_801CE9F4);

#include "overlays/plchar/Char_SelectScriptAndStep.h"

MATCH void func_801CEB84(void) {
    Actor* work = g_SpadWork;

    if ((g_ActorSlots[work->unk_06].flags_00 == 0 || g_ActorSlots[work->unk_06].unk_01 == 1) &&
        g_AreaCameraMoving == 0) {
        work->unk_06 = 0;
        g_SpadWork->unk_03 -= 2;
    }
}

INCLUDE_ASM(func_801CEC18);

/* Char_SpawnActor variant (shared body in plchar/Char_SpawnActor.h, 57 instructions): this one adds 0x200 to the sampled
 * height and sets link_0B to 1, and keeps the args in $s2/$s3/$s4 with the constant in $s1; the template body with those two
 * edits and MATCH_REG pins still saves $s2 first where retail saves $s3 first (first difference at +0x4). */
INCLUDE_ASM(func_801CEE24);

MATCH void func_801CEF10(void) {
    SYS_DISPATCH_TASK(D_801CF614, 3, g_SpadWork);
}

INCLUDE_ASM(func_801CEF54);

INCLUDE_ASM(func_801CEFCC);

INCLUDE_ASM(func_801CF0EC);

INCLUDE_ASM(func_801CF184);

MATCH void func_801CF328(void) {
    SYS_DISPATCH_TASK(D_801CF620, 2, g_SpadWork);
}

MATCH void Char_StartTurn(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CF534(void) {
    g_GameState->mode_12B.s8_value = 0;
}

MATCH void func_801CF544(void) {
    g_GameState->mode_12B.s8_value = 0;
}

MATCH void func_801CF554(void) {
    g_GameState->mode_12B.s8_value = 0;
}

MATCH void func_801CF564(void) {
    D_801CF62C[g_SpadWork->unk_2C]();
}

MATCH void func_801CF5A8(void) {
    D_801CF638[g_SpadWork->unk_2C]();
}
