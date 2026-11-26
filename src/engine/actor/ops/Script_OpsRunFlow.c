#include "engine/game/00/game_00.h"

/* Opcodes 0x00 to 0x0F of the actor script: flow control. */
typedef enum ActorScriptFlow {
    ACTOR_SCRIPT_FLOW_JUMP             = 1,  /* jump to the target; a labelled target seeks its label record */
    ACTOR_SCRIPT_FLOW_LOOP             = 2,  /* args: [offset] [times]; jump back a counted number of times */
    ACTOR_SCRIPT_FLOW_CALL_AREA_SCRIPT = 3,  /* args: [index]; call the area handler and take the task facing */
    ACTOR_SCRIPT_FLOW_IF_VAR_EQUALS    = 4,  /* args: [value] [var] [then_lo] [then_hi] [else_lo] [else_hi]; branch on a script variable equal to the value */
    ACTOR_SCRIPT_FLOW_IF_VARS_EQUAL    = 5,  /* args: [var] [var] ...; branch when two script variables are equal */
    ACTOR_SCRIPT_FLOW_IF_VAR_LESS      = 6,  /* args: [value] [var] ...; branch when the variable is below the value */
    ACTOR_SCRIPT_FLOW_IF_VARS_LESS     = 7,  /* args: [var] [var] ...; branch when the first variable is below the second */
    ACTOR_SCRIPT_FLOW_IF_VAR_MASK      = 8,  /* args: [mask] [var] ...; branch when the variable has any mask bit */
    ACTOR_SCRIPT_FLOW_IF_VARS_MASK     = 9,  /* args: [var] [var] ...; branch when the first variable has any bit of the second */
    ACTOR_SCRIPT_FLOW_SKIP             = 10, /* skip the two-byte label record */
    ACTOR_SCRIPT_FLOW_END              = 11, /* end the script: cursor to the start */
    ACTOR_SCRIPT_FLOW_SHOW_BATTLERS    = 12, /* args: [show]; show or hide the party battlers */
    ACTOR_SCRIPT_FLOW_SET_POSITION     = 13, /* args: [x] [x_half] [y] [y_half]; place the actor or the party */
    ACTOR_SCRIPT_FLOW_RUN_SCRIPT       = 14, /* args: [script] [flags] [route] ...; start an actor script */
    ACTOR_SCRIPT_FLOW_RUN_TALK_SCRIPT  = 15, /* args: [talk] [flags] [route] ...; start the script of the talk for the leading character */
} ActorScriptFlow;

/* The message ids of one talk, one per character. */
typedef struct TalkMessageRow {
    u8 ids[11];
} TalkMessageRow;

/* func_801A8F94 */
/* Runs flow opcodes until a movement or wait opcode; returns the facing selection. */
MATCH u8 Script_OpsRunFlow(ScriptState* state, u8* base, s32 seed) {
    s32                 left;
    s32                 sel;
    s8                  arg_size;
    u8                  group;
    void*               obj;
    AreaScriptCallback* table;

    sel = seed;
    for (;;) {
        group = base[state->cursor] & 0xF0;
        if (!(group < 0x10 || group == 0xA0 || group == 0xB0))
            break;
        if (group < 0x10) {
            switch (base[state->cursor]) {
                case ACTOR_SCRIPT_FLOW_JUMP:
                    if ((base[state->cursor + 1] & 0xC0) == 0x40) {
                        state->cursor = (u16)(base[state->cursor + 1] << 8 | base[state->cursor + 2]);
                        state->cursor = Script_FindLabel(state, (u8)state->cursor, base);
                    } else {
                        state->cursor += (u16)(base[state->cursor + 1] << 8 | base[state->cursor + 2]);
                    }
                    break;
                case ACTOR_SCRIPT_FLOW_LOOP:
                    if (state->count != 0) {
                        if (--state->count == 0) {
                            state->cursor += 3;
                            break;
                        }
                        state->cursor += (s8)base[state->cursor + 1];
                    } else {
                        state->count = base[state->cursor + 2];
                        state->cursor += (s8)base[state->cursor + 1];
                    }
                    break;
                case ACTOR_SCRIPT_FLOW_IF_VAR_EQUALS:
                    left = base[state->cursor + 1];
                    goto if_equal;
                case ACTOR_SCRIPT_FLOW_IF_VARS_EQUAL:
                    left = Script_ReadValue(base[state->cursor + 1]);
                if_equal:
                    if (Script_ReadValue(base[state->cursor + 2]) == left)
                        state->cursor = (u16)((base + state->cursor)[3] << 8 | (base + state->cursor)[4]);
                    else
                        state->cursor = (u16)((base + state->cursor)[5] << 8 | (base + state->cursor)[6]);
                    state->cursor = Script_FindLabel(state, (u8)state->cursor, base);
                    break;
                case ACTOR_SCRIPT_FLOW_IF_VAR_LESS:
                    left = base[state->cursor + 1];
                    goto if_less;
                case ACTOR_SCRIPT_FLOW_IF_VARS_LESS:
                    left = Script_ReadValue(base[state->cursor + 1]);
                if_less:
                    if (Script_ReadValue(base[state->cursor + 2]) < left)
                        state->cursor = (u16)((base + state->cursor)[3] << 8 | (base + state->cursor)[4]);
                    else
                        state->cursor = (u16)((base + state->cursor)[5] << 8 | (base + state->cursor)[6]);
                    state->cursor = Script_FindLabel(state, (u8)state->cursor, base);
                    break;
                case ACTOR_SCRIPT_FLOW_IF_VAR_MASK:
                    left = base[state->cursor + 1];
                    goto if_mask;
                case ACTOR_SCRIPT_FLOW_IF_VARS_MASK:
                    left = Script_ReadValue(base[state->cursor + 1]);
                if_mask:
                    if (Script_ReadValue(base[state->cursor + 2]) & left)
                        state->cursor = (u16)((base + state->cursor)[3] << 8 | (base + state->cursor)[4]);
                    else
                        state->cursor = (u16)((base + state->cursor)[5] << 8 | (base + state->cursor)[6]);
                    state->cursor = Script_FindLabel(state, (u8)state->cursor, base);
                    break;
                case ACTOR_SCRIPT_FLOW_CALL_AREA_SCRIPT:
                    obj   = g_AreaLoads[g_GameAreaId];
                    table = FIELD(AreaScriptCallback*, obj, 0x3Cu);
                    table[(base + state->cursor)[1]](obj);
                    sel = TASK(Actor)->direction;
                    state->cursor += 2;
                    break;
                case ACTOR_SCRIPT_FLOW_SKIP:
                    state->cursor += 2;
                    break;
                case ACTOR_SCRIPT_FLOW_END:
                    state->cursor = 0;
                    break;
                case ACTOR_SCRIPT_FLOW_SHOW_BATTLERS:
                    if (base[state->cursor + 1] != 0)
                        Party_BattlersShow();
                    else
                        Party_BattlersHide();
                    state->cursor += 2;
                    break;
                case ACTOR_SCRIPT_FLOW_SET_POSITION:
                    if (Actor_GetOwner() == 2) {
                        COORD_INT(g_PartyPos.x)  = (base + state->cursor)[1];
                        COORD_FRAC(g_PartyPos.x) = ((base + state->cursor)[2] != 0) << 0xF;
                        COORD_INT(g_PartyPos.y)  = (base + state->cursor)[3];
                        COORD_FRAC(g_PartyPos.y) = ((base + state->cursor)[4] != 0) << 0xF;
                        g_ScrollHeight           = Area_HeightSample(g_PartyPos.x.fixed, g_PartyPos.y.fixed);
                        sel                      = 0xFF;
                    } else {
                        COORD_INT(TASK(Actor)->pos.x)  = (base + state->cursor)[1];
                        COORD_FRAC(TASK(Actor)->pos.x) = ((base + state->cursor)[2] != 0) << 0xF;
                        COORD_INT(TASK(Actor)->pos.y)  = (base + state->cursor)[3];
                        COORD_FRAC(TASK(Actor)->pos.y) = ((base + state->cursor)[4] != 0) << 0xF;
                        COORD_INT(TASK(Actor)->pos.z)  = Area_HeightSample(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed);
                    }
                    state->cursor += 5;
                    break;
                case ACTOR_SCRIPT_FLOW_RUN_SCRIPT:
                    left = base[state->cursor + 1];
                    goto run_script;
                case ACTOR_SCRIPT_FLOW_RUN_TALK_SCRIPT:
                    left = ((TalkMessageRow*)s_TalkMessageIds)[base[state->cursor + 1]].ids[g_GameState->chr.character_id];
                run_script:
                    state->flags |= 0x40;
                    TASK(Actor)->option_flags |= ACTOR_OPT_ROUTE_LOCKED;
                    if ((base[state->cursor + 3] & 1) != 0)
                        TASK(Actor)->header.flags |= ACTOR_FLAG_STEP_MOVE;
                    else
                        TASK(Actor)->header.flags &= ~ACTOR_FLAG_STEP_MOVE;
                    TASK(Actor)->mirror = base[state->cursor + 2];
                    if ((base[state->cursor + 3] & 2) != 0) {
                        Script_Begin((u8)(left & BYTE_MASK), base[state->cursor + 4]);
                        state->cursor += 1;
                    } else {
                        Script_Select((u8)(left & BYTE_MASK));
                    }
                    state->cursor += 4;
                    break;
            }
        } else if (group == 0xA0) {
            arg_size = D_801821C0[base[state->cursor] & 3](base + state->cursor);
            if (arg_size < 0)
                break;
            state->cursor += arg_size + 1;
        } else {
            Script_OpsRunSound(state, base);
            state->cursor += 1;
        }
    }
    return sel;
}
