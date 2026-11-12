#include "plp349_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CF5EC[g_Task->header.step]();
}

MATCH void Char_StartTurnTeepo(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}

#include "overlays/plchar/Char_RunStepScriptTeepo.h"

MATCH void func_801CE610(void) {
    SYS_DISPATCH_TASK(D_801CF5F8, 2, g_Task);
}

MATCH void func_801CE654(void) {
    SYS_DISPATCH_TASK(D_801CF600, 3, g_Task);
}

MATCH void func_801CE698(void) {
    u8 direction;

    direction = g_Task->direction_08;
    if (!(direction & 1)) {
        g_Task->direction_08 = (direction - 1) & 7;
        if (!(func_801CF184() & 0xFF)) {
            g_Task->direction_08 = (g_Task->direction_08 + 2) & 7;
            if (!(func_801CF184() & 0xFF)) {
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

MATCH s32 func_801CEC18(s16 x, s16 y) {
    CHAR_PROBE_CELL_CODE(Char_SpawnLinkedActor);
}

INCLUDE_ASM(Char_SpawnLinkedActor);

MATCH void func_801CEF10(void) {
    SYS_DISPATCH_TASK(D_801CF614, 3, g_Task);
}

MATCH void func_801CEF54(void) {
    /* FAKE: retail reads SND_PlayCue as void(s32). */
    ((void (*)(s32))SND_PlayCue)(g_Task->unk_2C + 0x100);
    Actor_RequestScript(((g_Task->direction_08 - 1) / 2) + 0x42);
    g_Task->unk_0A = 8;
    g_Task->unk_03 = 1;
}

#include "overlays/plchar/Char_UpdateLinkedFacing.h"

#include "overlays/plchar/Char_ClearPanelModeIfUnused.h"

INCLUDE_ASM(func_801CF184);

MATCH void func_801CF328(void) {
    SYS_DISPATCH_TASK(D_801CF620, 2, g_Task);
}

#include "overlays/plchar/Char_StartTurn.h"

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CF534(void) {
    g_Game.current->u.field.mode_12B.s8_value = 0;
}

MATCH void func_801CF544(void) {
    g_Game.current->u.field.mode_12B.s8_value = 0;
}

MATCH void func_801CF554(void) {
    g_Game.current->u.field.mode_12B.s8_value = 0;
}

MATCH void func_801CF564(void) {
    D_801CF62C[g_Task->unk_2C]();
}

MATCH void func_801CF5A8(void) {
    D_801CF638[g_Task->unk_2C]();
}
