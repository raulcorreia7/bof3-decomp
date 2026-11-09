#include "plp025_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CFFA8[g_Task->header.step]();
}

INCLUDE_ASM(func_801CE448);

#include "overlays/plchar/func_801CE628.h"

MATCH void func_801CE72C(void) {
    SYS_DISPATCH_TASK(D_801CFFB4, 2, g_Task);
}

#include "overlays/plchar/func_801CE770.h"

INCLUDE_ASM(func_801CEA94);

#include "overlays/plchar/Char_AdvanceScript.h"

#include "overlays/plchar/Char_ProbeCellSpawn.h"

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801CF12C(void) {
    SYS_DISPATCH_TASK(D_801CFFC0, 2, g_Task);
}

#include "overlays/plchar/Char_StartTurn.h"

MATCH void Char_RunStepScript(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_AWAY, CHARACTER_FACING_BACK);
}

MATCH void func_801CF338(void) {
    SYS_DISPATCH_TASK(D_801CFFCC, 2, g_Task);
}

INCLUDE_ASM(func_801CF37C);

#include "overlays/plchar/func_801CF564.h"

INCLUDE_ASM(func_801CF5D4);

MATCH s32 func_801CF738(s32 arg0) {
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
        v0 = func_801BDD58(*(s32*)(D_80143FFC + s2), *(s32*)(D_80144000 + s2), (*(s16*)(D_80144006 + s2)) + 0x200, 1,
                           (Actor*)((u8*)&g_Game + s1));
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

INCLUDE_ASM(func_801CF808);

MATCH void func_801CF924(void) {
    SYS_DISPATCH_TASK(D_801CFFD4, 2, g_Task);
}

#include "overlays/plchar/Char_StartTurnMomo.h"

/* Runs one route step script: facing 5 requests script 0x41 and facing 3 requests 0x40,
 * the reverse of the script ids in CHAR_RUN_STEP_SCRIPT (plchar.h). */
#include "overlays/plchar/Char_AdvanceFacingTurn.h"

MATCH void func_801CFB30(void) {
    SYS_DISPATCH_TASK(D_801CFFE0, 2, g_Task);
}

INCLUDE_ASM(func_801CFB74);

#include "overlays/plchar/Char_ClaimLinkSlot.h"

#include "overlays/plchar/Char_PollScriptRequest.h"

MATCH void func_801CFF20(void) {
    D_801CFFEC[g_Task->unk_2C]();
}

MATCH void func_801CFF64(void) {
    D_801CFFF8[g_Task->unk_2C]();
}
