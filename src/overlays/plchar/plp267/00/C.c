#include "plp267_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D0988[g_Task->header.step]();
}

#include "overlays/plchar/Char_StartTurnGarr.h"

#include "overlays/plchar/Char_RunStepScriptGarr.h"

MATCH void func_801CE610(void) {
    SYS_DISPATCH_TASK(D_801D0994, 2, g_Task);
}

/* func_801CE654 */
#include "overlays/plchar/PlChar_RunGarrFieldTask.h"

MATCH void PlChar_RunGarrFieldTask(void) {
    PLCHAR_RUN_GARR_FIELD_TASK(func_801CEAE0);
}

#include "overlays/plchar/Char_TickPauseTimer.h"

/* func_801CE8AC */
#include "overlays/plchar/PlChar_FindGarrActorSlot.h"

#include "overlays/plchar/PlChar_FollowerInReach.h"

#include "overlays/plchar/PlChar_ProbeFacingFollower.h"

MATCH void func_801CEBFC(void) {
    SYS_DISPATCH_TASK(D_801D099C, 2, g_Task);
}

#include "overlays/plchar/Char_StartTurn.h"

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CEE08(void) {
    Actor_StepAnimLoop();
}

MATCH void func_801CEE28(void) {
    SYS_DISPATCH_TASK(D_801D09A8, 2, g_Task);
}

MATCH void func_801CEE6C(void) {
    SYS_DISPATCH_TASK(D_801D09B0, 3, g_Task);
}

MATCH void Char_FaceFreeDirection(void) {
    CHAR_FACE_FREE_DIRECTION(func_801CF99C, func_801CFB40);
}

#include "overlays/plchar/Char_RunPersonalAction.h"

#include "overlays/plchar/Char_AdvancePaletteScript.h"

#include "overlays/plchar/Char_StartFacingScript.h"

#include "overlays/plchar/Char_ClearSlotRefIfUnused.h"

MATCH s32 func_801CF420(s16 x, s16 y) {
    CHAR_PROBE_CELL_CODE(Char_SpawnLinkedActor);
}

INCLUDE_ASM(Char_SpawnLinkedActor);

MATCH void func_801CF718(void) {
    SYS_DISPATCH_TASK(D_801D09C4, 3, g_Task);
}

MATCH void func_801CF75C(void) {
    CHAR_START_FACING_TURN(func_801CFB40);
}

MATCH void func_801CF7C8(void) {
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
            g_SpawnedActors[g_Task->param.actor_slot].unk_08 = g_Task->direction_08;
            if (g_Task->option_flags == 0) {
                g_Task->option_flags = 1;
            }
            g_SpawnedActors[g_Task->param.actor_slot].unk_0A = g_Task->option_flags;
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 11));
        }
    }
}

#include "overlays/plchar/Char_ClearModeIfUnused.h"

INCLUDE_ASM(func_801CF99C);

MATCH void func_801CFB40(void) {
    s16 dist;
    s32 x;
    s32 y;

    CHAR_PROBE_FACING_CLEARANCE(dist, x, y)
}

MATCH void func_801CFCA4(void) {
    SYS_DISPATCH_TASK(D_801D09D0, 2, g_Task);
}

#include "overlays/plchar/Char_StartNearestFacingTurn.h"

#include "overlays/plchar/Char_RunStepScriptRyuAdult.h"

MATCH void func_801CFED8(void) {
    SYS_DISPATCH_TASK(D_801D09DC, 2, g_Task);
}

#include "overlays/plchar/Char_WalkStep.h"

INCLUDE_ASM(func_801D0268);

#include "overlays/plchar/Char_AdvanceScript.h"

#include "overlays/plchar/Char_ProbeCellSpawn.h"

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801D0900(void) {
    D_801D09E8[g_Task->unk_2C]();
}

MATCH void func_801D0944(void) {
    D_801D09F4[g_Task->unk_2C]();
}
