#include "plp056_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D0858[g_Task->header.step]();
}

#include "overlays/plchar/func_801CE448.h"

#include "overlays/plchar/func_801CE628.h"

MATCH void func_801CE72C(void) {
    SYS_DISPATCH_TASK(D_801D0864, 2, g_Task);
}

#include "overlays/plchar/func_801CE770.h"

#include "overlays/plchar/Char_RunFacingProbe.h"

MATCH void func_801CEA94(void){CHAR_RUN_FACING_PROBE()}
#include "overlays/plchar/Char_AdvanceScript.h"

#include "overlays/plchar/Char_ProbeCellSpawn.h"

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801CF12C(void) {
    SYS_DISPATCH_TASK(D_801D0870, 2, g_Task);
}

#include "overlays/plchar/Char_StartTurn.h"

/* Runs one route step script: facing 5 requests script 0x41 and facing 3 requests 0x40,
 * the reverse of the script ids in CHAR_RUN_STEP_SCRIPT (plchar.h). */
#include "overlays/plchar/Char_AdvanceFacingTurn.h"

MATCH void func_801CF338(void) {
    SYS_DISPATCH_TASK(D_801D087C, 2, g_Task);
}

MATCH void func_801CF37C(void) {
    CHAR_START_FREE_FACING;
}

#include "overlays/plchar/Char_ClaimLinkSlot.h"

#include "overlays/plchar/Char_PollScriptRequest.h"

MATCH void func_801CF728(void) {
    SYS_DISPATCH_TASK(D_801D0888, 2, g_Task);
}

#include "overlays/plchar/Char_StartTurnPeco.h"

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CF934(void) {
    Actor_StepAnimLoop();
}

MATCH void func_801CF954(void) {
    SYS_DISPATCH_TASK(D_801D0894, 2, g_Task);
}

MATCH void func_801CF998(void) {
    SYS_DISPATCH_TASK(D_801D089C, 3, g_Task);
}

MATCH void Char_FaceFreeDirection(void) {
    CHAR_FACE_FREE_DIRECTION(func_801D04C8, func_801D066C);
}

#include "overlays/plchar/Char_RunPersonalAction.h"

#include "overlays/plchar/Char_AdvancePaletteScript.h"

#include "overlays/plchar/Char_StartFacingScript.h"

#include "overlays/plchar/Char_ClearSlotRefIfUnused.h"

MATCH s32 func_801CFF4C(s16 x, s16 y) {
    CHAR_PROBE_CELL_CODE(Char_SpawnLinkedActor);
}

/* func_801D0158 */
#include "overlays/plchar/Char_SpawnLinkedActor.h"

MATCH void func_801D0244(void) {
    SYS_DISPATCH_TASK(D_801D08B0, 3, g_Task);
}

MATCH void func_801D0288(void) {
    CHAR_START_FACING_TURN(func_801D066C);
}

MATCH void func_801D02F4(void) {
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

/* Returns nonzero when a record, rock, or blocking cell occupies the current facing. */
MATCH s32 func_801D04C8(void) {
    /* FAKE: pure C is 0x1A0 vs 0x1A4; retail loads the work pointer before the frame. */
    FAKE_REG(Actor*, task, "a1");
    /* FAKE: pure C is 0x1A0 vs 0x1A4; retail keeps the facing index in v1. */
    FAKE_REG(u8, direction, "v1");
    /* FAKE: pure C is 0x1A0 vs 0x1A4; retail reuses v0 for the steps and probe flag. */
    FAKE_REG(s32, value, "v0");
    /* FAKE: pure C is 0x1A0 vs 0x1A4; retail keeps the x coordinate in s1. */
    FAKE_REG(s32, x, "s1");
    /* FAKE: pure C is 0x1A0 vs 0x1A4; retail keeps the y coordinate in s0. */
    FAKE_REG(s32, y, "s0");
    /* FAKE: pure C is 0x1A0 vs 0x1A4; retail loads the y base into v1. */
    FAKE_REG(s32, pos_y, "v1");
    /* FAKE: pure C is 0x1A0 vs 0x1A4; retail keeps the blocked flag in s2. */
    FAKE_REG(s32, blocked, "s2");
    /* FAKE: pure C is 0x1A0 vs 0x1A4; retail passes x in a0 before the y probe. */
    FAKE_REG(s32, pos_x, "a0");
    /* FAKE: pure C is 0x1A0 vs 0x1A4; retail sets the range mode in a2. */
    FAKE_REG(s32, range_mode, "a2");
    /* FAKE: pure C is 0x1A0 vs 0x1A4; retail compares the rock result with -1 in v1. */
    FAKE_REG(s32, sentinel, "v1");
    s32 cell;

    task = g_Task;
    FAKE_USE(task); /* FAKE: pure C is 0x1A0; the work pointer load follows the prologue. */
    direction = task->direction_08;
    FAKE_USE(direction); /* FAKE: pure C is 0x1A0; the facing index uses v0. */
    range_mode = 0;
    value      = g_FacingSteps[direction].x;
    pos_x      = task->pos.x.fixed;
    value *= 2;
    FAKE_USE(value); /* FAKE: pure C is 0x1A0; x absorbs the doubled step in s1. */
    x     = pos_x + value;
    pos_x = x;
    FAKE_USE(pos_x); /* FAKE: pure C is 0x1A0; the x argument moves before the y probe. */
    value = g_FacingStepY[direction * 2];
    FAKE_USE(value); /* FAKE: pure C is 0x1A0; the y step stays in s0. */
    pos_y = task->pos.y.fixed;
    FAKE_USE(pos_y); /* FAKE: pure C is 0x1A0; the y base loads into s0. */
    y     = pos_y + value * 2;
    value = Actor_FindInRange(pos_x, y, range_mode) != -1;
    FAKE_USE(value); /* FAKE: pure C is 0x1A0; the flag compare moves into the call slot. */
    blocked  = value;
    value    = ((s8 (*)(void))Game_FindRockAhead)();
    sentinel = -1;
    if ((s8)value != sentinel) {
        blocked = 1;
    }

    cell = Area_GetCellCode(x >> 16, y >> 16);
    if ((u8)(cell + 0x10) < 2 || (u8)cell == 0xF4 || (u8)(cell + 0xA) < 2) {
        blocked = 1;
    }
    if ((x & HALF_MASK) != 0) {
        cell = Area_GetCellCode((s16)((x >> 16) + 1), y >> 16);
        if ((u8)(cell + 0x10) < 2 || (u8)cell == 0xF4 || (u8)(cell + 0xA) < 2) {
            blocked = 1;
        }
    }
    if ((y & HALF_MASK) != 0) {
        cell = Area_GetCellCode(x >> 16, (s16)((y >> 16) + 1));
        if ((u8)(cell + 0x10) < 2 || (u8)cell == 0xF4 || (u8)(cell + 0xA) < 2) {
            blocked = 1;
        }
    }
    return blocked;
}

MATCH void func_801D066C(void) {
    s16 dist;
    s32 x;
    s32 y;

    CHAR_PROBE_FACING_CLEARANCE(dist, x, y)
}

MATCH void func_801D07D0(void) {
    D_801D08BC[g_Task->unk_2C]();
}

MATCH void func_801D0814(void) {
    D_801D08C8[g_Task->unk_2C]();
}
