#include "plp034_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D02F4[g_Task->header.step]();
}

#include "overlays/plchar/func_801CE448.h"

#include "overlays/plchar/func_801CE628.h"

MATCH void func_801CE72C(void) {
    SYS_DISPATCH_TASK(D_801D0300, 2, g_Task);
}

#include "overlays/plchar/func_801CE770.h"

INCLUDE_ASM(func_801CEA94);

#include "overlays/plchar/Char_AdvanceScript.h"

#include "overlays/plchar/Char_ProbeCellSpawn.h"

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801CF12C(void) {
    SYS_DISPATCH_TASK(D_801D030C, 2, g_Task);
}

#include "overlays/plchar/Char_StartTurn.h"

#include "overlays/plchar/Char_RunStepScriptTeepo.h"

MATCH void func_801CF338(void) {
    SYS_DISPATCH_TASK(D_801D0318, 2, g_Task);
}

MATCH void func_801CF37C(void) {
    SYS_DISPATCH_TASK(D_801D0320, 3, g_Task);
}

MATCH void func_801CF3C0(void) {
    u8 direction;

    direction = g_Task->direction_08;
    if (!(direction & 1)) {
        g_Task->direction_08 = (direction - 1) & 7;
        if (!(func_801CFEAC() & 0xFF)) {
            g_Task->direction_08 = (g_Task->direction_08 + 2) & 7;
            if (!(func_801CFEAC() & 0xFF)) {
                g_Task->direction_08 = (g_Task->direction_08 - 2) & 7;
            }
        }
    }
    /* FAKE: retail reads SND_PlayCue as void(s32). */
    ((void (*)(s32))SND_PlayCue)(g_Task->unk_2C + 0x100);
    Actor_RequestScript((((s32)(g_Task->direction_08 - 1) / 2) + 0x42) & 0xFF);
    g_Task->param.unk_0B = 0;
    g_Task->unk_06       = 0;
    g_Task->unk_0A       = 8;
    g_Task->unk_03       = 1;
}

#include "overlays/plchar/Char_RunPersonalAction.h"

#include "overlays/plchar/Char_AdvancePaletteScript.h"

#include "overlays/plchar/Char_StartFacingScript.h"

#include "overlays/plchar/Char_ClearSlotRefIfUnused.h"

MATCH s32 func_801CF940(s16 x, s16 y) {
    CHAR_PROBE_CELL_CODE(Char_SpawnLinkedActor);
}

INCLUDE_ASM(Char_SpawnLinkedActor);

MATCH void func_801CFC38(void) {
    SYS_DISPATCH_TASK(D_801D0334, 3, g_Task);
}

MATCH void func_801CFC7C(void) {
    /* FAKE: retail reads SND_PlayCue as void(s32). */
    ((void (*)(s32))SND_PlayCue)(g_Task->unk_2C + 0x100);
    Actor_RequestScript((((s32)(g_Task->direction_08 - 1) / 2) + 0x42) & 0xFF);
    g_Task->unk_0A = 8;
    g_Task->unk_03 = 1;
}

#include "overlays/plchar/Char_UpdateLinkedFacing.h"

#include "overlays/plchar/Char_ClearPanelModeIfUnused.h"

INCLUDE_ASM(func_801CFEAC);

MATCH void func_801D0050(void) {
    SYS_DISPATCH_TASK(D_801D0340, 2, g_Task);
}

MATCH void Char_StartTurnRei(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801D025C(void) {
    g_Game.current->u.field.mode_12B.s8_value = 0;
}

MATCH void func_801D026C(void) {
    D_801D034C[g_Task->unk_2C]();
}

MATCH void func_801D02B0(void) {
    D_801D0358[g_Task->unk_2C]();
}
