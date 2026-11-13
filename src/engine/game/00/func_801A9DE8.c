#include "game_00.h"

/* Opcodes 0xF0 to 0xFF of the actor script table: the record group that moves
 * the task (or the camera, Actor_GetOwner() == 2) in z, walks it to a cell,
 * waits, and touches the cell palette. Named from the case bodies. */
/* Opcodes 0xF0 to 0xFF of the actor script table: the record group that moves
 * the task (or the camera, Actor_GetOwner() == 2) in z, walks it to a cell,
 * waits, and touches the cell palette. Named from the case bodies. */
typedef enum ActorScriptMotionOp {
    ACTOR_SCRIPT_MOTION_CLEAR_SCRIPT_ACTIVE = 0xF0, /* clear GAME_FLAG_SCRIPT_ACTIVE */
    ACTOR_SCRIPT_MOTION_SET_SCRIPT_ACTIVE   = 0xF1, /* set GAME_FLAG_SCRIPT_ACTIVE */
    ACTOR_SCRIPT_MOTION_MOVE_SCRIPT         = 0xF2, /* args: [script_id] [steps]; start the move script */
    ACTOR_SCRIPT_MOTION_MOVE_SCRIPT_RAMP_Z  = 0xF3, /* args: [script_id] [steps] [z]; also ramp vz to z */
    ACTOR_SCRIPT_MOTION_SET_Z_VELOCITY      = 0xF4, /* args: [z] [steps]; vz to target, stop vx and vy */
    ACTOR_SCRIPT_MOTION_STOP_MOVING         = 0xF5, /* clear GAME_CURSOR_FLAG_MOVING */
    ACTOR_SCRIPT_MOTION_SET_SCENE_STATE     = 0xF6, /* args: [value] -> g_SceneState.state_04 */
    ACTOR_SCRIPT_MOTION_WALK_TO             = 0xF7, /* args: [x] [y] [steps]; step to the cell, z follows */
    ACTOR_SCRIPT_MOTION_SET_ACTOR_MODE      = 0xF8, /* args: [mode]; func_801AC768 stores mode and walk fields */
    ACTOR_SCRIPT_MOTION_WAIT_WALK_ROUTE     = 0xF9, /* args: [a] [b]; step the walk, wait while it runs */
    ACTOR_SCRIPT_MOTION_SET_Z_POSITION      = 0xFA, /* args: [id] [keep] [z]; set z, stop the z move */
    ACTOR_SCRIPT_MOTION_SET_CELL_PALETTE    = 0xFB, /* Area_SetCellPalette at the cell; cue 1.3 when set */
    ACTOR_SCRIPT_MOTION_CLEAR_CELL_PALETTE  = 0xFC, /* Area_ClearCellPalette at the cell; cue 1.3, cleared */
    ACTOR_SCRIPT_MOTION_WAIT_SCRIPT_READY   = 0xFD, /* wait while the script stream reports not ready */
    ACTOR_SCRIPT_MOTION_PLAY_CUE_ON_SCRIPT  = 0xFE, /* args: [cue] [pc]; play 0x200|cue when record changed */
    ACTOR_SCRIPT_MOTION_WAIT                = 0xFF, /* hold the cursor at this record */
} ActorScriptMotionOp;

/* Entity spawn counter cell in scratchpad (signed 16-bit slot index). */
/* The entry cell at 0x1F800002 is stored through D_1F800002 and read back signed. */
MATCH u8 func_801A9DE8(GameCursorState* state, const u8* table, u8 value) {
    u8 byte;
    u8 result;

    byte = table[state->index_0A];
    switch (byte) {
        case ACTOR_SCRIPT_MOTION_CLEAR_SCRIPT_ACTIVE:
            Game_ClearScriptActive();
            return value;
        case ACTOR_SCRIPT_MOTION_SET_SCRIPT_ACTIVE:
            Game_SetScriptActive();
            return value;
        case ACTOR_SCRIPT_MOTION_MOVE_SCRIPT: {
            u8 next;

            value         = *(table + state->index_0A + 1);
            next          = *(table + state->index_0A + 2);
            state->unk_07 = next;
            if (next != 0) {
                if (Actor_GetOwner() != 2)
                    func_801ABBA8(state, value);
                else
                    func_801C5DFC(value);
            }
            state->index_0A += 2;
            break;
        }
        case ACTOR_SCRIPT_MOTION_MOVE_SCRIPT_RAMP_Z: {
            u8 next;

            value         = *(table + state->index_0A + 1);
            next          = *(table + state->index_0A + 2);
            state->unk_07 = next;
            if (next != 0) {
                if (Actor_GetOwner() != 2) {
                    Actor* work;
                    s32    den;

                    func_801ABBA8(state, value);
                    work     = g_Task;
                    den      = work->timer * state->unk_07;
                    work->vz = ((s16)((*(table + state->index_0A + 3) << 8) | *(table + state->index_0A + 4)) - (s16)COORD_INT(work->pos.z)) / den;
                    state->flags |= GAME_CURSOR_FLAG_MOVING;
                } else {
                    s16* counter;
                    s32  step;

                    counter    = (s16*)&D_1F800000;
                    *counter   = COORD_INT(g_Task->pos.z);
                    D_1F800002 = (s16)((*(table + state->index_0A + 3) << 8) | *(table + state->index_0A + 4));
                    func_801C5DFC(value);
                    step       = (0x80 / g_AreaCameraStep) * D_80143FC3;
                    D_80143F5C = ((SP_REF(s16, 0x2u) - *counter) << 16) / step;
                    state->flags |= 0x40;
                }
            }
            state->index_0A += 4;
            break;
        }
        case ACTOR_SCRIPT_MOTION_SET_Z_VELOCITY: {
            Actor* work;

            state->flags |= GAME_CURSOR_FLAG_MOVING;
            g_Task->timer = *(table + state->index_0A + 3);
            if (g_Task->timer == 0)
                g_Task->timer = 1;
            work     = g_Task;
            work->vz = ((s16)((*(table + state->index_0A + 1) << 8) | *(table + state->index_0A + 2)) - (s16)COORD_INT(work->pos.z)) / work->timer;
            work->vx = 0;
            work->vy = 0;
            state->index_0A += 3;
            break;
        }
        case ACTOR_SCRIPT_MOTION_STOP_MOVING:
            state->flags &= 0x7F;
            break;
        case ACTOR_SCRIPT_MOTION_WAIT_WALK_ROUTE: {
            Actor* work;

            if ((func_801AC33C(*(table + state->index_0A + 1), *(table + state->index_0A + 2)) << 24) != 0) {
                state->index_0A--;
                return 0xFF;
            }
            state->index_0A += 2;
            work  = g_Task;
            value = work->direction_08 & 0x7;
            break;
        }
        case ACTOR_SCRIPT_MOTION_SET_Z_POSITION: {
            u8     next;
            Actor* work;

            value         = *(table + state->index_0A + 1);
            next          = *(table + state->index_0A + 2);
            state->unk_07 = next;
            if (next != 0) {
                if (Actor_GetOwner() != 2) {
                    func_801ABBA8(state, value);
                    state->flags |= GAME_CURSOR_FLAG_MOVING;
                } else {
                    func_801C5DFC(value);
                    g_AreaCameraHeightStep = 0;
                    state->flags |= 0x40;
                }
            }
            work                   = g_Task;
            work->vz               = 0;
            COORD_INT(work->pos.z) = (u16)((*(table + state->index_0A + 3) << 8) | *(table + state->index_0A + 4));
            state->index_0A += 4;
            break;
        }
        case ACTOR_SCRIPT_MOTION_WAIT_SCRIPT_READY:
            if (Actor_StepAnimOnce() != 0)
                return value;
            g_Task->option_flags |= ACTOR_OPT_WAIT_STREAM;
            state->index_0A--;
            break;
        case ACTOR_SCRIPT_MOTION_PLAY_CUE_ON_SCRIPT: {
            Actor* work;
            u16    mode;

            if (g_GameStateIndex != GAME_REQUEST_BATTLE) {
                mode                = Actor_ReadState();
                work                = g_Task;
                GAME_ENTITY_COUNTER = mode;
                /* FAKE: counter store before work read. */
                FAKE_BARRIER();
                if ((work->script_pc != mode) && (mode == *(table + state->index_0A + 2)))
                    SND_PlayCue((u16)(0x200u | *(table + state->index_0A + 1)));
            }
            state->index_0A += 2;
            break;
        }
        case ACTOR_SCRIPT_MOTION_SET_SCENE_STATE:
            g_SceneState.state_04 = *(table + state->index_0A + 1);
            /* Retail shares the +1 cursor advance with case 0xF8. */
            goto advance_one;
        case ACTOR_SCRIPT_MOTION_WALK_TO: {
            s32 hi;
            s32 lo;

            hi = (*(table + state->index_0A + 1) << 16) | (*(table + state->index_0A + 2) << 8);
            lo = (*(table + state->index_0A + 3) << 16) | (*(table + state->index_0A + 4) << 8);
            func_801ABD68(hi, lo, *(table + state->index_0A + 5), state);
            value = *(table + state->index_0A + 6);
            if (Actor_GetOwner() == 1)
                state->unk_07 = 1;
            state->index_0A += 6;
            break;
        }
        case ACTOR_SCRIPT_MOTION_SET_ACTOR_MODE:
            func_801AC768(state, *(table + state->index_0A + 1), *(table + state->index_0A + 2), *(table + state->index_0A + 3), *(table + state->index_0A + 4));
        advance_one:
            state->index_0A += 1;
            break;
        case ACTOR_SCRIPT_MOTION_SET_CELL_PALETTE: {
            Actor* work;

            work   = g_Task;
            result = Area_SetCellPalette(COORD_INT(work->pos.x), COORD_INT(work->pos.y));
            /* Retail shares the cue check with case 0xFC. */
            goto queue_cue;
        }
        case ACTOR_SCRIPT_MOTION_CLEAR_CELL_PALETTE: {
            Actor* work;

            work   = g_Task;
            result = Area_ClearCellPalette(COORD_INT(work->pos.x), COORD_INT(work->pos.y));
        }
        queue_cue:
            if (result != 0)
                SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
            return value;
        case ACTOR_SCRIPT_MOTION_WAIT:
            state->index_0A--;
            return value;
    }
    return value;
}
