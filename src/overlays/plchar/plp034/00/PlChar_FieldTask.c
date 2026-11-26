#include "plp034_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D02F4[SELF(Actor)->header.step]();
}

#include "overlays/plchar/shared/func_801CE448.h"

#include "overlays/plchar/shared/func_801CE628.h"

MATCH void func_801CE72C(void) {
    SYS_DISPATCH_TASK(D_801D0300, 2, g_Self);
}

#include "overlays/plchar/shared/func_801CE770.h"

#include "overlays/plchar/shared/Char_RunFacingProbe.h"

MATCH void func_801CEA94(void){CHAR_RUN_FACING_PROBE()}
#include "overlays/plchar/shared/PlChar_AdvanceScript.h"

#include "overlays/plchar/shared/PlChar_ProbeCellSpawn.h"

#include "overlays/plchar/shared/PlChar_SpawnActor.h"

#include "overlays/plchar/shared/PlChar_ProbeFacingCell.h"

MATCH void func_801CF12C(void) {
    SYS_DISPATCH_TASK(D_801D030C, 2, g_Self);
}

#include "overlays/plchar/shared/PlChar_StartTurn.h"

#include "overlays/plchar/shared/PlChar_RunStepScriptTeepo.h"

MATCH void func_801CF338(void) {
    SYS_DISPATCH_TASK(D_801D0318, 2, g_Self);
}

MATCH void func_801CF37C(void) {
    SYS_DISPATCH_TASK(D_801D0320, 3, g_Self);
}

MATCH void func_801CF3C0(void) {
    u8 direction;

    direction = SELF(Actor)->direction;
    if (!(direction & 1)) {
        SELF(Actor)->direction = (direction - 1) & 7;
        if (!(func_801CFEAC() & 0xFF)) {
            SELF(Actor)->direction = (SELF(Actor)->direction + 2) & 7;
            if (!(func_801CFEAC() & 0xFF)) {
                SELF(Actor)->direction = (SELF(Actor)->direction - 2) & 7;
            }
        }
    }
    /* FAKE: retail reads SND_SEPlay as void(s32). */
    ((void (*)(s32))SND_SEPlay)(SELF(Actor)->unk_2C + 0x100);
    Script_Request((((s32)(SELF(Actor)->direction - 1) / 2) + 0x42) & 0xFF);
    SELF(Actor)->param.unk_0B = 0;
    SELF(Actor)->unk_06       = 0;
    SELF(Actor)->unk_0A       = 8;
    SELF(Actor)->unk_03       = 1;
}

#include "overlays/plchar/shared/PlChar_RunPersonalAction.h"

#include "overlays/plchar/shared/PlChar_AdvancePaletteScript.h"

#include "overlays/plchar/shared/PlChar_StartFacingScript.h"

#include "overlays/plchar/shared/PlChar_ClearSlotRefIfUnused.h"

MATCH s32 func_801CF940(s16 x, s16 y) {
    CHAR_PROBE_CELL_CODE(PlChar_SpawnLinkedActor);
}

/* func_801CFB4C */
#include "overlays/plchar/shared/PlChar_SpawnLinkedActor.h"

MATCH void func_801CFC38(void) {
    SYS_DISPATCH_TASK(D_801D0334, 3, g_Self);
}

MATCH void func_801CFC7C(void) {
    /* FAKE: retail reads SND_SEPlay as void(s32). */
    ((void (*)(s32))SND_SEPlay)(SELF(Actor)->unk_2C + 0x100);
    Script_Request((((s32)(SELF(Actor)->direction - 1) / 2) + 0x42) & 0xFF);
    SELF(Actor)->unk_0A = 8;
    SELF(Actor)->unk_03 = 1;
}

#include "overlays/plchar/shared/PlChar_UpdateLinkedFacing.h"

#include "overlays/plchar/shared/PlChar_ClearPanelModeIfUnused.h"

#include "overlays/plchar/shared/Char_ProbeFacingBlocked.h"
CHAR_DEFINE_PROBE_FACING_BLOCKED(func_801CFEAC);

MATCH void func_801D0050(void) {
    SYS_DISPATCH_TASK(D_801D0340, 2, g_Self);
}

MATCH void PlChar_StartTurnRei(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

#include "overlays/plchar/shared/PlChar_RunStepScript.h"

MATCH void func_801D025C(void) {
    g_Game.current->u.field.mode.value = 0;
}

MATCH void func_801D026C(void) {
    D_801D034C[SELF(Actor)->unk_2C]();
}

MATCH void func_801D02B0(void) {
    D_801D0358[SELF(Actor)->unk_2C]();
}
