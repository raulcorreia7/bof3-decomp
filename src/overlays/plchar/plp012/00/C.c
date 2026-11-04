#include "plp012_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CFD80[((u8*)g_SpadWork)[2]]();
}

INCLUDE_ASM(func_801CE448);

#include "overlays/plchar/func_801CE628.h"

MATCH void func_801CE72C(void) {
    SYS_DISPATCH_TASK(D_801CFD8C, 2, g_SpadWork);
}

#include "overlays/plchar/func_801CE770.h"

INCLUDE_ASM(func_801CEA94);

#include "overlays/plchar/Char_AdvanceScript.h"

INCLUDE_ASM(func_801CED1C);

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801CF12C(void) {
    SYS_DISPATCH_TASK(D_801CFD98, 2, g_SpadWork);
}

#include "overlays/plchar/Char_StartTurn.h"

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CF338(void) {
    SYS_DISPATCH_TASK(D_801CFDA4, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CF37C);

MATCH void func_801CF494(void) {
    if (g_ActorSlots[g_SpadWork->unk_0B].flags_00 == 0) {
        g_GameState->mode_12B.s8_value = 0;
    }
    func_8014D978();
}

MATCH void func_801CF500(void) {
    SYS_DISPATCH_TASK(D_801CFDAC, 2, g_SpadWork);
}

/* This copy turns between facings 3 and 5; the image's own are the header's. */
MATCH void Char_StartTurn_801CF544(void) {
    CHAR_START_TURN(3, 5);
}

/* This copy selects scripts 0x40 and 0x41 at facings 5 and 3; the image's own are the header's. */
MATCH void Char_RunStepScript_801CF610(void) {
    CHAR_RUN_STEP_SCRIPT(5, 3);
}

MATCH void func_801CF70C(void) {
    SYS_DISPATCH_TASK(D_801CFDB8, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CF750);

MATCH void func_801CF938(void) {
    if (g_SpadWork->unk_09 == 0) {
        g_GameState->mode_12B.s8_value = 0;
        g_GameFlags &= ~0x1000;
    } else {
        g_SpadWork->unk_09--;
        func_801B0DFC();
    }
    func_8014D978();
}

INCLUDE_ASM(func_801CF9A8);

INCLUDE_ASM(func_801CFB0C);

INCLUDE_ASM(func_801CFBDC);

MATCH void func_801CFCF8(void) {
    D_801CFDC0[g_SpadWork->unk_2C]();
}

MATCH void func_801CFD3C(void) {
    D_801CFDCC[g_SpadWork->unk_2C]();
}
