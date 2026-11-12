#include "plp567_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D078C[g_Task->header.step]();
}

#include "overlays/plchar/Char_StartTurn.h"

#include "overlays/plchar/Char_RunStepScriptMomo.h"

MATCH void func_801CE610(void) {
    SYS_DISPATCH_TASK(D_801D0798, 2, g_Task);
}

INCLUDE_ASM(func_801CE654);

#include "overlays/plchar/Char_ClaimLinkSlot.h"

#include "overlays/plchar/Char_PollScriptRequest.h"

MATCH void func_801CEA00(void) {
    SYS_DISPATCH_TASK(D_801D07A4, 2, g_Task);
}

#include "overlays/plchar/Char_StartTurnPeco.h"

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CEC0C(void) {
    Actor_StepAnimLoop();
}

MATCH void func_801CEC2C(void) {
    SYS_DISPATCH_TASK(D_801D07B0, 2, g_Task);
}

MATCH void func_801CEC70(void) {
    SYS_DISPATCH_TASK(D_801D07B8, 3, g_Task);
}

MATCH void Char_FaceFreeDirection(void) {
    CHAR_FACE_FREE_DIRECTION(func_801CF7A0, func_801CF944);
}

#include "overlays/plchar/Char_RunPersonalAction.h"

#include "overlays/plchar/Char_AdvancePaletteScript.h"

#include "overlays/plchar/Char_StartFacingScript.h"

#include "overlays/plchar/Char_ClearSlotRefIfUnused.h"

MATCH s32 func_801CF224(s16 x, s16 y) {
    CHAR_PROBE_CELL_CODE(Char_SpawnLinkedActor);
}

INCLUDE_ASM(Char_SpawnLinkedActor);

MATCH void func_801CF51C(void) {
    SYS_DISPATCH_TASK(D_801D07CC, 3, g_Task);
}

MATCH void func_801CF560(void) {
    CHAR_START_FACING_TURN(func_801CF944);
}

MATCH void func_801CF5CC(void) {
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        Actor_RequestScript(g_Task->direction_08);
        g_Task->unk_03 = 2;
        return;
    }
    if (g_Task->unk_0A != 0) {
        g_Task->unk_0A--;
        if (g_Task->unk_0A == 0) {
            /* FAKE: retail reads SND_PlayCue as void(s32). */
            ((void (*)(s32))SND_PlayCue)(g_Task->unk_2C + 0x100);
            g_ActorSlots[g_Task->param.actor_slot].unk_08 = g_Task->direction_08;
            if (g_Task->option_flags == 0) {
                g_Task->option_flags = 1;
            }
            g_ActorSlots[g_Task->param.actor_slot].unk_0A = g_Task->option_flags;
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 11));
        }
    }
}

#include "overlays/plchar/Char_ClearModeIfUnused.h"

INCLUDE_ASM(func_801CF7A0);

MATCH void func_801CF944(void) {
    s16 dist;
    s32 x;
    s32 y;

    CHAR_PROBE_FACING_CLEARANCE(dist, x, y)
}

MATCH void func_801CFAA8(void) {
    SYS_DISPATCH_TASK(D_801D07D8, 2, g_Task);
}

#include "overlays/plchar/Char_StartNearestFacingTurn.h"

#include "overlays/plchar/Char_RunStepScriptRyuAdult.h"

MATCH void func_801CFCDC(void) {
    SYS_DISPATCH_TASK(D_801D07E4, 2, g_Task);
}

#include "overlays/plchar/Char_WalkStep.h"

INCLUDE_ASM(func_801D006C);

#include "overlays/plchar/Char_AdvanceScript.h"

#include "overlays/plchar/Char_ProbeCellSpawn.h"

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801D0704(void) {
    D_801D07F0[g_Task->unk_2C]();
}

MATCH void func_801D0748(void) {
    D_801D07FC[g_Task->unk_2C]();
}
