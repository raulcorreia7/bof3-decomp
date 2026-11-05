#include "plp056_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D0858[((u8*)g_SpadWork)[2]]();
}

INCLUDE_ASM(func_801CE448);

#include "overlays/plchar/func_801CE628.h"

MATCH void func_801CE72C(void) {
    SYS_DISPATCH_TASK(D_801D0864, 2, g_SpadWork);
}

#include "overlays/plchar/func_801CE770.h"

INCLUDE_ASM(func_801CEA94);

#include "overlays/plchar/Char_AdvanceScript.h"

INCLUDE_ASM(func_801CED1C);

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801CF12C(void) {
    SYS_DISPATCH_TASK(D_801D0870, 2, g_SpadWork);
}

#include "overlays/plchar/Char_StartTurn.h"

/* Runs one route step script: facing 5 requests script 0x41 and facing 3 requests 0x40,
 * the reverse of the script ids in CHAR_RUN_STEP_SCRIPT (plchar.h). */
#include "../../Char_AdvanceFacingTurn.h"

MATCH void func_801CF338(void) {
    SYS_DISPATCH_TASK(D_801D087C, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CF37C);

#include "overlays/plchar/Char_ClaimLinkSlot.h"

#include "overlays/plchar/Char_PollScriptRequest.h"

MATCH void func_801CF728(void) {
    SYS_DISPATCH_TASK(D_801D0888, 2, g_SpadWork);
}

MATCH void Char_StartTurn_801CF76C(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CF934(void) {
    func_8014D978();
}

MATCH void func_801CF954(void) {
    SYS_DISPATCH_TASK(D_801D0894, 2, g_SpadWork);
}

MATCH void func_801CF998(void) {
    SYS_DISPATCH_TASK(D_801D089C, 3, g_SpadWork);
}

#include "overlays/plchar/Char_TurnAndRequestScript.h"

INCLUDE_ASM(func_801CFADC);

#include "overlays/plchar/Char_AdvancePaletteScript.h"

#include "overlays/plchar/Char_SelectScriptAndStep.h"

#include "overlays/plchar/Char_ClearSlotRefIfUnused.h"

INCLUDE_ASM(func_801CFF4C);

/* Char_SpawnActor variant (shared body in plchar/Char_SpawnActor.h, 57 instructions): this one adds 0x200 to the sampled
 * height and sets link_0B to 1, and keeps the args in $s2/$s3/$s4 with the constant in $s1; the template body with those two
 * edits and MATCH_REG pins still saves $s2 first where retail saves $s3 first (first difference at +0x4). */
INCLUDE_ASM(func_801D0158);

MATCH void func_801D0244(void) {
    SYS_DISPATCH_TASK(D_801D08B0, 3, g_SpadWork);
}

MATCH void func_801D0288(void) {
    func_801D066C();
    Actor_RequestScript((g_SpadWork->direction_08 - 1) / 2 + 0x42);
    g_SpadWork->unk_0A = 0xB;
    g_SpadWork->unk_03 = 1;
}

INCLUDE_ASM(func_801D02F4);

#include "overlays/plchar/Char_ClearModeIfUnused.h"

INCLUDE_ASM(func_801D04C8);

INCLUDE_ASM(func_801D066C);

MATCH void func_801D07D0(void) {
    D_801D08BC[g_SpadWork->unk_2C]();
}

MATCH void func_801D0814(void) {
    D_801D08C8[g_SpadWork->unk_2C]();
}
