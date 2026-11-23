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
NON_MATCHING u8 Script_OpsRunWait(void* sub, s32 target, u8 value) {
    u8* code;
    u8* cmd;
    u8  slot;
    s32 tmp;
    u16 hit;
    u16 next;
    u8* index;

    code = (u8*)target;
    switch (code[FIELD(u16, sub, 0xAu)]) {
        case ACTOR_SCRIPT_WAIT_SNAP_PARTY_TO_SCROLL:
            g_PartyX       = g_AreaScrollTargetX;
            g_PartyY       = g_AreaScrollTargetY;
            g_ScrollHeight = Area_HeightSample(g_AreaScrollTargetX, g_AreaScrollTargetY);
            return value;
        case ACTOR_SCRIPT_WAIT_PLAY_CUE_ON_SCRIPT:
            if (g_GameStateIndex != GAME_REQUEST_BATTLE) {
                hit              = Actor_ReadState();
                SP_REF(u16, 0x0) = hit;
                if (TASK(Actor)->script_pc != hit) {
                    cmd = code + FIELD(u16, sub, 0xAu);
                    if (hit == cmd[3]) {
                        Actor_PlayCueByDistance(cmd[2] | (cmd[1] << 8), cmd[4]);
                    }
                }
            }
            next = FIELD(u16, sub, 0xAu) + 4;
        set_cursor:
            FIELD(u16, sub, 0xAu) = next;
        done:
            return value;
        case ACTOR_SCRIPT_WAIT_TOGGLE_ROUTE_STEP:
            TASK(Actor)->option_flags ^= 0x40;
            if (TASK(Actor)->option_flags & 0x40) {
                FIELD(s8, g_Task, 0x48u) = 0;
            } else {
                FIELD(s8, g_Task, 0x48u) = 1;
            }
            return value;
        case ACTOR_SCRIPT_WAIT_TOGGLE_NO_TARGET:
            TASK(Actor)->option_flags ^= ACTOR_OPT_NO_TARGET;
            return value;
        case ACTOR_SCRIPT_WAIT_SET_PARTY_SLOT_MOVE:
            index  = &D_1F800001;
            tmp    = -(g_CurrentActor - g_PartyActors) >> 3;
            *index = tmp;
            if ((u8)tmp >= 5U) {
                *index = 4;
            }
            cmd = code + FIELD(u16, sub, 0xAu);
            if (cmd[7] != 0) {
                slot                               = cmd[7];
                g_ActorTurnRamps[*index].frames_xy = slot;
                g_ActorTurnRamps[*index].frames_z  = slot;
                cmd                                = code + FIELD(u16, sub, 0xAu);
                g_ActorTurnRamps[*index].delta_z   = (s16)(cmd[6] | (cmd[5] << 8)) / g_ActorTurnRamps[*index].frames_z;
                cmd                                = code + FIELD(u16, sub, 0xAu);
                g_ActorTurnRamps[*index].delta_y   = (s16)(cmd[4] | (cmd[3] << 8)) / g_ActorTurnRamps[*index].frames_z;
                cmd                                = code + FIELD(u16, sub, 0xAu);
                g_ActorTurnRamps[*index].delta_x   = (s16)(cmd[2] | (cmd[1] << 8)) / g_ActorTurnRamps[*index].frames_z;
            } else {
                TASK(Actor)->angle_z = (s16)(cmd[6] | (cmd[5] << 8));
                cmd                  = code + FIELD(u16, sub, 0xAu);
                TASK(Actor)->angle_y = (s16)(cmd[4] | (cmd[3] << 8));
                cmd                  = code + FIELD(u16, sub, 0xAu);
                TASK(Actor)->angle_x = (s16)(cmd[2] | (cmd[1] << 8));
            }
            *(u8*)sub |= 8;
            FIELD(u16, sub, 0xAu) += 7;
            goto done;
        case ACTOR_SCRIPT_WAIT_WAIT_PARTY_SLOT_MOVE:
            tmp             = -(g_CurrentActor - g_PartyActors) >> 3;
            SP_REF(s8, 0x1) = tmp;
            tmp &= BYTE_MASK;
            if ((u32)tmp < 4U && (g_ActorTurnRamps[tmp].frames_z + g_ActorTurnRamps[tmp].frames_xy) != 0) {
                goto back;
            }
            return value;
        case ACTOR_SCRIPT_WAIT_TOGGLE_PARTY_SLOT:
            index  = &D_1F800001;
            tmp    = -(g_CurrentActor - g_PartyActors) >> 3;
            *index = tmp;
            if (tmp & 0x80) {
                *index = 4;
            }
            g_ActorTurnRamps[(s8)*index].flags ^= 1;
            return value;
        case ACTOR_SCRIPT_WAIT_SET_UNK_06:
            slot = code[FIELD(u16, sub, 0xAu) + 1];
            FIELD(u16, sub, 0xAu) += 1;
            FIELD(u8, sub, 0x6u) = slot;
            return value;
        case ACTOR_SCRIPT_WAIT_UNLOCK_SCROLL:
            g_GameFlags &= ~GAME_FLAG_SCROLL_LOCK;
            *(u8*)sub |= 8;
            return value;
        case ACTOR_SCRIPT_WAIT_WAIT_MESSAGE:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                goto back;
            }
            return value;
        case ACTOR_SCRIPT_WAIT_WAIT_WINDOW_EFFECT:
            if (WINDOW_EFFECT_BUSY()) {
                goto back;
            }
            return value;
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
        case ACTOR_SCRIPT_WAIT_CALL_AREA_SCRIPT: {
            Actor* obj = g_AreaLoads[g_GameAreaId];
            (*(void (**)())((code[FIELD(u16, sub, 0xAu) + 1] * 4) + obj->pos.z.fixed))(obj);
            value = TASK(Actor)->direction;
            next  = FIELD(u16, sub, 0xAu) + 1;
            goto set_cursor;
        }
        case ACTOR_SCRIPT_WAIT_WAIT_BATTLE:
            if (g_GameStateIndex == GAME_REQUEST_BATTLE) {
                goto back;
            }
            return value;
        default:
            goto done;
    }
back:
    next = FIELD(u16, sub, 0xAu) - 1;
    goto set_cursor;
}
#else
INCLUDE_ASM(Script_OpsRunWait);
#endif
