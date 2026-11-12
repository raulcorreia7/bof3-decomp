#include "plp012_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801CFD80[g_Task->header.step]();
}

#include "overlays/plchar/func_801CE448.h"

#include "overlays/plchar/func_801CE628.h"

MATCH void func_801CE72C(void) {
    SYS_DISPATCH_TASK(D_801CFD8C, 2, g_Task);
}

#include "overlays/plchar/func_801CE770.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801CEA94(void) {
    s32 cx;
    s32 cy;
    s16 x;
    s16 y;
    s32 slot;
    s32 probe;

    g_Task->unk_0A--;
    if (g_Task->unk_0A == 0) {
        cx   = g_Task->pos.x.fixed + g_FacingSteps[g_Task->direction_08].x * 2;
        cy   = g_Task->pos.y.fixed + g_FacingSteps[g_Task->direction_08].y * 2;
        slot = func_801BDE14(cx, cy, 0);
        if (slot != -1) {
            g_Actors[slot].interaction_flags |= ACTOR_FLAG_INTERACTION_PENDING;
        }
        x     = cx >> 16;
        y     = cy >> 16;
        probe = Char_ProbeCellSpawn(x, y);
        if ((probe & BYTE_MASK) == 0) {
            if ((cx & HALF_MASK) != 0) {
                probe = Char_ProbeCellSpawn((s16)(x + 1), y);
            }
            if ((probe & BYTE_MASK) == 0) {
                if ((cy & HALF_MASK) != 0) {
                    Char_ProbeCellSpawn(x, (s16)(y + 1));
                }
            }
        }
        g_Task->header.step++;
    }
    Actor_StepAnimOnce();
}
#else
INCLUDE_ASM(func_801CEA94);
#endif

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

#include "overlays/plchar/Char_ClaimHelperSlotStep.h"

MATCH void func_801CF37C(void) {
    Char_ClaimHelperSlotStep();
}

#include "overlays/plchar/Char_ClearModeIfSlotFree.h"

MATCH void func_801CF500(void) {
    SYS_DISPATCH_TASK(D_801CFDAC, 2, g_Task);
}

#include "overlays/plchar/Char_StartTurnGarr.h"

#include "overlays/plchar/Char_RunStepScriptGarr.h"

MATCH void func_801CF70C(void) {
    SYS_DISPATCH_TASK(D_801CFDB8, 2, g_Task);
}

/* func_801CF750 */
#include "overlays/plchar/PlChar_RunGarrFieldTask.h"

MATCH void PlChar_RunGarrFieldTask(void) {
    PLCHAR_RUN_GARR_FIELD_TASK(func_801CFBDC);
}

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

/* func_801CF9A8 */
#include "overlays/plchar/PlChar_FindGarrActorSlot.h"

/* func_801CFB0C */
#include "overlays/plchar/Plchar_FollowerInReach.h"

#include "overlays/plchar/Plchar_ProbeFacingFollower.h"

MATCH void func_801CFCF8(void) {
    D_801CFDC0[g_Task->unk_2C]();
}

MATCH void func_801CFD3C(void) {
    D_801CFDCC[g_Task->unk_2C]();
}
