#include "plp026_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D0A54[g_Task->header.step]();
}

#include "overlays/plchar/func_801CE448.h"

#include "overlays/plchar/func_801CE628.h"

MATCH void func_801CE72C(void) {
    SYS_DISPATCH_TASK(D_801D0A60, 2, g_Task);
}

#include "overlays/plchar/func_801CE770.h"

INCLUDE_ASM(func_801CEA94);

#include "overlays/plchar/Char_AdvanceScript.h"

#include "overlays/plchar/Char_ProbeCellSpawn.h"

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801CF12C(void) {
    SYS_DISPATCH_TASK(D_801D0A6C, 2, g_Task);
}

#include "overlays/plchar/Char_StartTurn.h"

#include "overlays/plchar/Char_RunStepScriptGarr.h"

MATCH void func_801CF338(void) {
    SYS_DISPATCH_TASK(D_801D0A78, 2, g_Task);
}

/* func_801CF37C */
#include "overlays/plchar/PlChar_RunGarrFieldTask.h"

MATCH void PlChar_RunGarrFieldTask(void) {
    PLCHAR_RUN_GARR_FIELD_TASK(func_801CF808);
}

#include "overlays/plchar/func_801CF564.h"

/* func_801CF5D4 */
#include "overlays/plchar/PlChar_FindGarrActorSlot.h"

#include "overlays/plchar/Plchar_FollowerInReach.h"

#include "overlays/plchar/Plchar_ProbeFacingFollower.h"

MATCH void func_801CF924(void) {
    SYS_DISPATCH_TASK(D_801D0A80, 2, g_Task);
}

#include "overlays/plchar/Char_StartTurnPeco.h"

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CFB30(void) {
    Actor_StepAnimLoop();
}

MATCH void func_801CFB50(void) {
    SYS_DISPATCH_TASK(D_801D0A8C, 2, g_Task);
}

MATCH void func_801CFB94(void) {
    SYS_DISPATCH_TASK(D_801D0A94, 3, g_Task);
}

MATCH void Char_FaceFreeDirection(void) {
    CHAR_FACE_FREE_DIRECTION(func_801D06C4, func_801D0868);
}

#include "overlays/plchar/Char_RunPersonalAction.h"

#include "overlays/plchar/Char_AdvancePaletteScript.h"

#include "overlays/plchar/Char_StartFacingScript.h"

#include "overlays/plchar/Char_ClearSlotRefIfUnused.h"

MATCH s32 func_801D0148(s16 x, s16 y) {
    CHAR_PROBE_CELL_CODE(Char_SpawnLinkedActor);
}

INCLUDE_ASM(Char_SpawnLinkedActor);

MATCH void func_801D0440(void) {
    SYS_DISPATCH_TASK(D_801D0AA8, 3, g_Task);
}

MATCH void func_801D0484(void) {
    CHAR_START_FACING_TURN(func_801D0868);
}

MATCH void func_801D04F0(void) {
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

INCLUDE_ASM(func_801D06C4);

MATCH void func_801D0868(void) {
    s16 dist;
    s32 x;
    s32 y;

    CHAR_PROBE_FACING_CLEARANCE(dist, x, y)
}

MATCH void func_801D09CC(void) {
    D_801D0AB4[g_Task->unk_2C]();
}

MATCH void func_801D0A10(void) {
    D_801D0AC0[g_Task->unk_2C]();
}
