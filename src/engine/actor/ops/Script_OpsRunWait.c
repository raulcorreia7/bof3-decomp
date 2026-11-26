#include "engine/game/00/game_00.h"

/* Opcodes 0xD0 to 0xDF of the actor script: camera, waits, cell palette. */
typedef enum ActorScriptWait {
    ACTOR_SCRIPT_WAIT_SNAP_PARTY_TO_SCROLL      = 0xD0, /* put the party at the scroll target */
    ACTOR_SCRIPT_WAIT_PLAY_CUE_ON_SCRIPT        = 0xD1, /* args: [cue_hi] [cue_lo] [pc] [index]; play a cue when the script reaches the record */
    ACTOR_SCRIPT_WAIT_TOGGLE_ROUTE_STEP         = 0xD2, /* toggle the route-step option bit */
    ACTOR_SCRIPT_WAIT_TOGGLE_NO_TARGET          = 0xD3, /* toggle the no-target option bit */
    ACTOR_SCRIPT_WAIT_SET_PARTY_SLOT_MOVE       = 0xD4, /* args: three position deltas and a step count; move a party slot */
    ACTOR_SCRIPT_WAIT_WAIT_PARTY_SLOT_MOVE      = 0xD5, /* hold while the party slot is moving */
    ACTOR_SCRIPT_WAIT_TOGGLE_PARTY_SLOT         = 0xD6, /* toggle a party slot flag */
    ACTOR_SCRIPT_WAIT_SET_UNK_06                = 0xD7, /* args: [value]; store in the interaction state */
    ACTOR_SCRIPT_WAIT_UNLOCK_SCROLL             = 0xD8, /* clear the scroll lock */
    ACTOR_SCRIPT_WAIT_WAIT_MESSAGE              = 0xD9, /* hold while a message request runs */
    ACTOR_SCRIPT_WAIT_WAIT_WINDOW_EFFECT        = 0xDA, /* hold while the window effect is busy */
    ACTOR_SCRIPT_WAIT_MOVE_AND_SET_CELL_PALETTE = 0xDB, /* apply the velocity, follow the height, then set the cell palette */
    ACTOR_SCRIPT_WAIT_SET_CELL_PALETTE          = 0xDC, /* set the palette of the actor cell */
    ACTOR_SCRIPT_WAIT_CLEAR_CELL_PALETTE        = 0xDD, /* clear the palette of the actor cell */
    ACTOR_SCRIPT_WAIT_CALL_AREA_SCRIPT          = 0xDE, /* args: [index]; call the area handler */
    ACTOR_SCRIPT_WAIT_WAIT_BATTLE               = 0xDF, /* hold while a battle request runs */
} ActorScriptWait;

/* func_801AA470 */
/* Runs one wait or camera opcode. */
#ifdef NON_MATCHING
NON_MATCHING u8 Script_OpsRunWait(ScriptState* state, u8* base, u8 value) {
    u8*       cmd;
    u8        frames;
    u16       pc;
    u32       index;
    AreaLoad* area;

    switch (base[state->cursor]) {
        case ACTOR_SCRIPT_WAIT_SNAP_PARTY_TO_SCROLL:
            g_PartyX       = g_AreaScrollTargetX;
            g_PartyY       = g_AreaScrollTargetY;
            g_ScrollHeight = Area_HeightSample(g_PartyX, g_PartyY);
            return value;
        case ACTOR_SCRIPT_WAIT_PLAY_CUE_ON_SCRIPT:
            if (g_GameStateIndex != GAME_REQUEST_BATTLE) {
                pc                        = Actor_ReadState();
                SPAD(0u)->cells.halves[0] = pc;
                if (TASK(Actor)->script_pc != pc) {
                    cmd = base + state->cursor;
                    if (pc == cmd[3])
                        Actor_PlayCueByDistance(cmd[1] << 8 | cmd[2], cmd[4]);
                }
            }
            state->cursor += 4;
            break;
        case ACTOR_SCRIPT_WAIT_TOGGLE_ROUTE_STEP:
            TASK(Actor)->option_flags ^= 0x40;
            if (TASK(Actor)->option_flags & 0x40)
                FIELD(s8, g_Task, 0x48u) = 0;
            else
                FIELD(s8, g_Task, 0x48u) = 1;
            break;
        case ACTOR_SCRIPT_WAIT_TOGGLE_NO_TARGET:
            TASK(Actor)->option_flags ^= ACTOR_OPT_NO_TARGET;
            break;
        case ACTOR_SCRIPT_WAIT_SET_PARTY_SLOT_MOVE:
            g_ScratchPad.cells.bytes[1] = g_CurrentActor - g_PartyActors;
            if (g_ScratchPad.cells.bytes[1] >= 5)
                g_ScratchPad.cells.bytes[1] = 4;
            frames = (base + state->cursor)[7];
            if (frames != 0) {
                g_ActorTurnRamps[g_ScratchPad.cells.bytes[1]].frames_z = g_ActorTurnRamps[g_ScratchPad.cells.bytes[1]].frames_xy = frames;
                g_ActorTurnRamps[g_ScratchPad.cells.bytes[1]].delta_z = (s16)((base + state->cursor)[5] << 8 | (base + state->cursor)[6]) / g_ActorTurnRamps[g_ScratchPad.cells.bytes[1]].frames_z;
                g_ActorTurnRamps[g_ScratchPad.cells.bytes[1]].delta_y = (s16)((base + state->cursor)[3] << 8 | (base + state->cursor)[4]) / g_ActorTurnRamps[g_ScratchPad.cells.bytes[1]].frames_z;
                g_ActorTurnRamps[g_ScratchPad.cells.bytes[1]].delta_x = (s16)((base + state->cursor)[1] << 8 | (base + state->cursor)[2]) / g_ActorTurnRamps[g_ScratchPad.cells.bytes[1]].frames_z;
            } else {
                TASK(Actor)->angle_z = (s16)((base + state->cursor)[5] << 8 | (base + state->cursor)[6]);
                TASK(Actor)->angle_y = (s16)((base + state->cursor)[3] << 8 | (base + state->cursor)[4]);
                TASK(Actor)->angle_x = (s16)((base + state->cursor)[1] << 8 | (base + state->cursor)[2]);
            }
            state->flags |= 8;
            state->cursor += 7;
            break;
        case ACTOR_SCRIPT_WAIT_WAIT_PARTY_SLOT_MOVE:
            D_1F800001 = g_CurrentActor - g_PartyActors;
            index      = D_1F800001;
            if (index < 4) {
                if (g_ActorTurnRamps[index].frames_z + g_ActorTurnRamps[index].frames_xy == 0)
                    return value;
                state->cursor--;
            }
            break;
        case ACTOR_SCRIPT_WAIT_TOGGLE_PARTY_SLOT:
            g_ScratchPad.cells.bytes[1] = g_CurrentActor - g_PartyActors;
            if ((s8)g_ScratchPad.cells.bytes[1] < 0)
                g_ScratchPad.cells.bytes[1] = 4;
            g_ActorTurnRamps[(s8)g_ScratchPad.cells.bytes[1]].flags ^= 1;
            return value;
        case ACTOR_SCRIPT_WAIT_SET_UNK_06:
            state->pad_06 = (base + state->cursor)[1];
            state->cursor += 1;
            break;
        case ACTOR_SCRIPT_WAIT_UNLOCK_SCROLL:
            g_GameFlags &= ~GAME_FLAG_SCROLL_LOCK;
            state->flags |= 8;
            break;
        case ACTOR_SCRIPT_WAIT_WAIT_MESSAGE:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE)
                return value;
            state->cursor--;
            break;
        case ACTOR_SCRIPT_WAIT_WAIT_WINDOW_EFFECT:
            if (!WINDOW_EFFECT_BUSY())
                return value;
            state->cursor--;
            break;
        case ACTOR_SCRIPT_WAIT_MOVE_AND_SET_CELL_PALETTE:
            Actor_ApplyVelocity();
            COORD_INT(TASK(Actor)->pos.z) = Area_HeightSample(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed);
            /* fallthrough */
        case ACTOR_SCRIPT_WAIT_SET_CELL_PALETTE:
            Area_CellSetPalette(COORD_INT(TASK(Actor)->pos.x), COORD_INT(TASK(Actor)->pos.y));
            return value;
        case ACTOR_SCRIPT_WAIT_CLEAR_CELL_PALETTE:
            Area_CellClearPalette(COORD_INT(TASK(Actor)->pos.x), COORD_INT(TASK(Actor)->pos.y));
            return value;
        case ACTOR_SCRIPT_WAIT_CALL_AREA_SCRIPT:
            area = g_AreaLoads[g_GameAreaId];
            ((AreaScriptCallback*)area->unk_3C)[(base + state->cursor)[1]](area);
            value = TASK(Actor)->direction;
            state->cursor += 1;
            break;
        case ACTOR_SCRIPT_WAIT_WAIT_BATTLE:
            if (g_GameStateIndex != GAME_REQUEST_BATTLE)
                return value;
            state->cursor--;
            break;
    }
    return value;
}
#else
INCLUDE_ASM(Script_OpsRunWait);
#endif
