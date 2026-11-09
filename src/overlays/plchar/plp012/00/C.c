#include "plp012_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CFD80[g_Task->header.step]();
}

INCLUDE_ASM(func_801CE448);

#include "overlays/plchar/func_801CE628.h"

MATCH void func_801CE72C(void) {
    SYS_DISPATCH_TASK(D_801CFD8C, 2, g_Task);
}

#include "overlays/plchar/func_801CE770.h"

INCLUDE_ASM(func_801CEA94);

#include "overlays/plchar/Char_AdvanceScript.h"

#include "overlays/plchar/Char_ProbeCellSpawn.h"

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801CF12C(void) {
    SYS_DISPATCH_TASK(D_801CFD98, 2, g_Task);
}

#include "overlays/plchar/Char_StartTurn.h"

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CF338(void) {
    SYS_DISPATCH_TASK(D_801CFDA4, 2, g_Task);
}

INCLUDE_ASM(func_801CF37C);

#include "overlays/plchar/Char_ClearModeIfSlotFree.h"

MATCH void func_801CF500(void) {
    SYS_DISPATCH_TASK(D_801CFDAC, 2, g_Task);
}

#include "overlays/plchar/Char_StartTurnGarr.h"

#include "overlays/plchar/Char_RunStepScriptGarr.h"

MATCH void func_801CF70C(void) {
    SYS_DISPATCH_TASK(D_801CFDB8, 2, g_Task);
}

INCLUDE_ASM(func_801CF750);

MATCH void func_801CF938(void) {
    if (g_Task->timer == 0) {
        g_Game.current->u.field.mode_12B.s8_value = 0;
        g_GameFlags &= ~0x1000;
    } else {
        g_Task->timer--;
        func_801B0DFC();
    }
    Actor_StepAnimLoop();
}

INCLUDE_ASM(func_801CF9A8);

MATCH s32 func_801CFB0C(s32 arg0) {
    {
        register s32 s0 asm("$16") = 1;
        register s32 s2 asm("$18");
        register s32 s1 asm("$17");
        register s32 v0 asm("$2");
        register s32 v1 asm("$3");

        v0 = g_PartySize;
        if (s0 >= v0) {
            goto L801CEAC0;
        }
        v1 = (arg0) & 0xFF;
        v0 = v1 << 3;
        v0 = v0 - v1;
        v0 = v0 << 2;
        v0 = v0 + v1;
        s2 = v0 << 2;
        s1 = 0x140;
    L801CEA54:
        v0 = func_801BDD58(*(s32*)(D_80143FFC + s2), *(s32*)(D_80144000 + s2), (*(s16*)(D_80144006 + s2)) + 0x200, 1, (Actor*)((u8*)&g_Game + s1));
        if (!(v0 & 0xFF)) {
            v0 = g_PartySize;
            s0 = s0 + 1;
            if (s0 < v0) {
                s1 = s1 + 0x140;
                goto L801CEA54;
            }
            goto L801CEAC0;
        }
        v0 = 1;
    L801CEAC4:
        return v0;
    L801CEAC0:
        v0 = 0;
        goto L801CEAC4;
    }
}

INCLUDE_ASM(func_801CFBDC);

MATCH void func_801CFCF8(void) {
    D_801CFDC0[g_Task->unk_2C]();
}

MATCH void func_801CFD3C(void) {
    D_801CFDCC[g_Task->unk_2C]();
}
