#include "plp015_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CFB84[((u8*)g_SpadWork)[2]]();
}

INCLUDE_ASM(func_801CE448);

#include "overlays/plchar/func_801CE628.h"

MATCH void func_801CE72C(void) {
    SYS_DISPATCH_TASK(D_801CFB90, 2, g_SpadWork);
}

#include "overlays/plchar/func_801CE770.h"

INCLUDE_ASM(func_801CEA94);

#include "overlays/plchar/Char_AdvanceScript.h"

INCLUDE_ASM(func_801CED1C);

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801CF12C(void) {
    SYS_DISPATCH_TASK(D_801CFB9C, 2, g_SpadWork);
}

#include "overlays/plchar/Char_StartTurn.h"

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CF338(void) {
    SYS_DISPATCH_TASK(D_801CFBA8, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CF37C);

INCLUDE_ASM(func_801CF494);

MATCH void func_801CF500(void) {
    SYS_DISPATCH_TASK(D_801CFBB0, 2, g_SpadWork);
}

/* This copy turns between facings 3 and 5; the image's own are the header's. */
MATCH void Char_StartTurn_801CF544(void) {
    CHAR_START_TURN(3, 5);
}

/* Runs one route step script: facing 5 requests script 0x41 and facing 3 requests 0x40,
 * the reverse of the script ids in CHAR_RUN_STEP_SCRIPT (plchar.h). */
MATCH void func_801CF610(void) {
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

MATCH void func_801CF70C(void) {
    SYS_DISPATCH_TASK(D_801CFBBC, 2, g_SpadWork);
}

INCLUDE_ASM(func_801CF750);

INCLUDE_ASM(func_801CF91C);

MATCH void func_801CFA28(void) {
    if (g_SpadWork->unk_07 != 0) {
        if (func_8014DAEC() & 0xFF) {
            Actor_RequestScript(g_SpadWork->direction_08);
            g_SpadWork->unk_07 = 0;
        }
    } else if ((func_8014DAEC() & 0xFF) && (g_ActorSlots[g_SpadWork->unk_0B].flags_00 == 0)) {
        g_SpadWork->unk_2B             = 0;
        g_GameState->mode_12B.s8_value = 0;
    }
}

MATCH void func_801CFAFC(void) {
    D_801CFBC8[g_SpadWork->unk_2C]();
}

MATCH void func_801CFB40(void) {
    D_801CFBD4[g_SpadWork->unk_2C]();
}
