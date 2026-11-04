#include "plp025_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CFFA8[((u8*)g_SpadWork)[2]]();
}

INCLUDE_ASM(func_801CE448);

#include "overlays/plchar/func_801CE628.h"

MATCH void func_801CE72C(void) {
    SYS_DISPATCH_TASK(D_801CFFB4, 2, g_SpadWork);
}

#include "overlays/plchar/func_801CE770.h"

INCLUDE_ASM(func_801CEA94);

#include "overlays/plchar/Char_AdvanceScript.h"

INCLUDE_ASM(func_801CED1C);

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801CF12C(void) {
    SYS_DISPATCH_TASK(D_801CFFC0, 2, g_SpadWork);
}

#include "overlays/plchar/Char_StartTurn.h"

MATCH void Char_RunStepScript(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_AWAY, CHARACTER_FACING_BACK);
}

MATCH void func_801CF338(void) {
    SYS_DISPATCH_TASK(D_801CFFCC, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CF37C);

INCLUDE_ASM(func_801CF564);

INCLUDE_ASM(func_801CF5D4);

INCLUDE_ASM(func_801CF738);

INCLUDE_ASM(func_801CF808);

MATCH void func_801CF924(void) {
    SYS_DISPATCH_TASK(D_801CFFD4, 2, g_SpadWork);
}

MATCH void Char_StartTurn_801CF968(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

/* Runs one route step script: facing 5 requests script 0x41 and facing 3 requests 0x40,
 * the reverse of the script ids in CHAR_RUN_STEP_SCRIPT (plchar.h). */
MATCH void func_801CFA34(void) {
    if (g_SpadWork->direction_08 == g_SpadWork->unk_03) {
        switch (g_SpadWork->direction_08) {
            case 5:
                Actor_RequestScript(0x41);
                break;
            case 3:
                Actor_RequestScript(0x40);
                break;
        }
        g_SpadWork->state_02++;
    } else {
        g_SpadWork->unk_09--;
        if (g_SpadWork->unk_09 == 0) {
            g_SpadWork->unk_09       = 2;
            g_SpadWork->direction_08 = g_SpadWork->direction_08 + g_SpadWork->unk_0B;
            g_SpadWork->direction_08 &= 7;
            Actor_RequestScript(g_SpadWork->direction_08);
        }
    }
}

MATCH void func_801CFB30(void) {
    SYS_DISPATCH_TASK(D_801CFFE0, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CFB74);

#include "overlays/plchar/Char_ClaimLinkSlot.h"

#include "overlays/plchar/Char_PollScriptRequest.h"

MATCH void func_801CFF20(void) {
    D_801CFFEC[g_SpadWork->unk_2C]();
}

MATCH void func_801CFF64(void) {
    D_801CFFF8[g_SpadWork->unk_2C]();
}
