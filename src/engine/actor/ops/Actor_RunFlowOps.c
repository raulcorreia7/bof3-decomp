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

/* func_801A8F94 */
/* Runs flow opcodes until a movement or wait opcode; returns the facing selection. */
#ifdef NON_MATCHING
NON_MATCHING u8 Actor_RunFlowOps(ScriptState* state, u8* base, s32 seed) {
    s32                 left;
    s32                 sel;
    s32                 dist;
    s8                  step;
    void*               obj;
    AreaScriptCallback* table;

    sel = seed;
    for (;;) {
        switch (base[state->cursor] & 0xF0) {
            case 0x00:
                switch (base[state->cursor]) {
                    case ACTOR_SCRIPT_FLOW_JUMP:
                        if ((base[state->cursor + 1] & 0xC0) == 0x40) {
                            state->cursor = (u16)(base[state->cursor + 2] | (base[state->cursor + 1] << 8));
                            state->cursor = Actor_FindScriptLabel(state, (u8)state->cursor, base);
                        } else {
                            state->cursor = (u16)(state->cursor + base[state->cursor + 2] + (base[state->cursor + 1] << 8));
                        }
                        break;
                    case ACTOR_SCRIPT_FLOW_LOOP:
                        if (state->count == 0) {
                            state->count  = base[state->cursor + 2];
                            state->cursor = (u16)(state->cursor + (s8)base[state->cursor + 1]);
                        } else {
                            state->count--;
                            if (state->count != 0)
                                state->cursor = (u16)(state->cursor + (s8)base[state->cursor + 1]);
                            else
                                state->cursor += 3;
                        }
                        break;
                    case ACTOR_SCRIPT_FLOW_CALL_AREA_SCRIPT:
                        obj   = g_AreaLoads[g_GameAreaId];
                        table = FIELD(AreaScriptCallback*, obj, 0x3Cu);
                        table[base[state->cursor + 1]](obj);
                        sel = g_Task->direction;
                        state->cursor += 2;
                        break;
                    case ACTOR_SCRIPT_FLOW_IF_VAR_EQUALS:
                        left = base[state->cursor + 1];
                        if (Script_ReadValue(base[state->cursor + 2]) == left)
                            state->cursor = (u16)(base[state->cursor + 3] | (base[state->cursor + 4] << 8));
                        else
                            state->cursor = (u16)(base[state->cursor + 5] | (base[state->cursor + 6] << 8));
                        state->cursor = Actor_FindScriptLabel(state, (u8)state->cursor, base);
                        break;
                    case ACTOR_SCRIPT_FLOW_IF_VARS_EQUAL:
                        left = Script_ReadValue(base[state->cursor + 1]);
                        if (Script_ReadValue(base[state->cursor + 2]) == left)
                            state->cursor = (u16)(base[state->cursor + 3] | (base[state->cursor + 4] << 8));
                        else
                            state->cursor = (u16)(base[state->cursor + 5] | (base[state->cursor + 6] << 8));
                        state->cursor = Actor_FindScriptLabel(state, (u8)state->cursor, base);
                        break;
                    case ACTOR_SCRIPT_FLOW_IF_VAR_LESS:
                        left = base[state->cursor + 1];
                        if (Script_ReadValue(base[state->cursor + 2]) < left)
                            state->cursor = (u16)(base[state->cursor + 3] | (base[state->cursor + 4] << 8));
                        else
                            state->cursor = (u16)(base[state->cursor + 5] | (base[state->cursor + 6] << 8));
                        state->cursor = Actor_FindScriptLabel(state, (u8)state->cursor, base);
                        break;
                    case ACTOR_SCRIPT_FLOW_IF_VARS_LESS:
                        left = Script_ReadValue(base[state->cursor + 1]);
                        if (Script_ReadValue(base[state->cursor + 2]) < left)
                            state->cursor = (u16)(base[state->cursor + 3] | (base[state->cursor + 4] << 8));
                        else
                            state->cursor = (u16)(base[state->cursor + 5] | (base[state->cursor + 6] << 8));
                        state->cursor = Actor_FindScriptLabel(state, (u8)state->cursor, base);
                        break;
                    case ACTOR_SCRIPT_FLOW_IF_VAR_MASK:
                        left = base[state->cursor + 1];
                        if ((Script_ReadValue(base[state->cursor + 2]) & left) != 0)
                            state->cursor = (u16)(base[state->cursor + 3] | (base[state->cursor + 4] << 8));
                        else
                            state->cursor = (u16)(base[state->cursor + 5] | (base[state->cursor + 6] << 8));
                        state->cursor = Actor_FindScriptLabel(state, (u8)state->cursor, base);
                        break;
                    case ACTOR_SCRIPT_FLOW_IF_VARS_MASK:
                        left = Script_ReadValue(base[state->cursor + 1]);
                        if ((Script_ReadValue(base[state->cursor + 2]) & left) != 0)
                            state->cursor = (u16)(base[state->cursor + 3] | (base[state->cursor + 4] << 8));
                        else
                            state->cursor = (u16)(base[state->cursor + 5] | (base[state->cursor + 6] << 8));
                        state->cursor = Actor_FindScriptLabel(state, (u8)state->cursor, base);
                        break;
                    case ACTOR_SCRIPT_FLOW_SKIP:
                        state->cursor += 2;
                        break;
                    case ACTOR_SCRIPT_FLOW_END:
                        state->cursor = 0;
                        break;
                    case ACTOR_SCRIPT_FLOW_SHOW_BATTLERS:
                        if (base[state->cursor + 1] == 0)
                            Party_HideBattlers();
                        else
                            Party_ShowBattlers();
                        state->cursor += 2;
                        break;
                    case ACTOR_SCRIPT_FLOW_SET_POSITION:
                        if (Actor_GetOwner() == 2) {
                            g_PartyX       = (s32)((base[state->cursor + 1] << 16) | ((base[state->cursor + 2] != 0) << 15));
                            g_PartyY       = (s32)((base[state->cursor + 3] << 16) | ((base[state->cursor + 4] != 0) << 15));
                            g_ScrollHeight = Area_SampleHeight(g_PartyX, g_PartyY);
                            sel            = 0xFF;
                        } else {
                            g_Task->pos.x.fixed      = (s32)((base[state->cursor + 1] << 16) | ((base[state->cursor + 2] != 0) << 15));
                            g_Task->pos.y.fixed      = (s32)((base[state->cursor + 3] << 16) | ((base[state->cursor + 4] != 0) << 15));
                            COORD_INT(g_Task->pos.z) = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
                        }
                        state->cursor += 5;
                        break;
                    case ACTOR_SCRIPT_FLOW_RUN_SCRIPT:
                        left = base[state->cursor + 1];
                        state->flags |= 0x40;
                        g_Task->option_flags |= ACTOR_OPT_ROUTE_LOCKED;
                        if ((base[state->cursor + 3] & 1) != 0)
                            g_Task->header.flags |= ACTOR_FLAG_STEP_MOVE;
                        else
                            g_Task->header.flags &= ~ACTOR_FLAG_STEP_MOVE;
                        g_Task->mirror = base[state->cursor + 2];
                        if ((base[state->cursor + 3] & 2) != 0) {
                            Actor_BeginScript((u8)(left & BYTE_MASK), base[state->cursor + 4]);
                            state->cursor += 1;
                        } else {
                            Actor_SelectScript((u8)(left & BYTE_MASK));
                        }
                        state->cursor += 4;
                        break;
                    case ACTOR_SCRIPT_FLOW_RUN_TALK_SCRIPT:
                        left = s_TalkMessageIds[base[state->cursor + 1] * 11 + g_Game.current->chr.character_id];
                        state->flags |= 0x40;
                        g_Task->option_flags |= ACTOR_OPT_ROUTE_LOCKED;
                        if ((base[state->cursor + 3] & 1) != 0)
                            g_Task->header.flags |= ACTOR_FLAG_STEP_MOVE;
                        else
                            g_Task->header.flags &= ~ACTOR_FLAG_STEP_MOVE;
                        g_Task->mirror = base[state->cursor + 2];
                        if ((base[state->cursor + 3] & 2) != 0) {
                            Actor_BeginScript((u8)(left & BYTE_MASK), base[state->cursor + 4]);
                            state->cursor += 1;
                        } else {
                            Actor_SelectScript((u8)(left & BYTE_MASK));
                        }
                        state->cursor += 4;
                        break;
                }
                break;
            case 0xA0:
                dist = D_801821C0[base[state->cursor] & 3](base + state->cursor);
                step = (s8)dist;
                if (step < 0)
                    return (u8)(sel & BYTE_MASK);
                state->cursor = (u16)(state->cursor + step + 1);
                break;
            case 0xB0:
                Actor_RunSoundOps(state, base);
                state->cursor += 1;
                break;
            default:
                return (u8)(sel & BYTE_MASK);
        }
    }
}
#else
INCLUDE_ASM(Actor_RunFlowOps);
#endif
