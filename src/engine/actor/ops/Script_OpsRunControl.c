#include "engine/game/00/game_00.h"

/* Opcodes 0xE0 to 0xEF of the actor script: start and end scripts, actor flags. */
typedef enum ActorScriptControl {
    ACTOR_SCRIPT_CONTROL_START_FACING_PARTY     = 0xE0, /* args: [wait]; script of the facing opposite the leader, mark the interaction moving */
    ACTOR_SCRIPT_CONTROL_START_SELECTED         = 0xE1, /* args: [script] [wait]; select the actor script and mark it pending */
    ACTOR_SCRIPT_CONTROL_SET_WAIT               = 0xE2, /* args: [wait_hi] [wait_lo]; set the interaction wait */
    ACTOR_SCRIPT_CONTROL_START_DIRECTION        = 0xE3, /* args: [wait]; start with the current direction */
    ACTOR_SCRIPT_CONTROL_RELEASE_ROUTE          = 0xE4, /* release the route lock and the wait on the stream */
    ACTOR_SCRIPT_CONTROL_END_SCRIPT             = 0xE5, /* end the script and restore the actor mode */
    ACTOR_SCRIPT_CONTROL_CLEAR_ACTOR            = 0xE6, /* clear the actor header flags */
    ACTOR_SCRIPT_CONTROL_SELECT_ROUTE           = 0xE7, /* args: [route]; select the scene route and stop moving */
    ACTOR_SCRIPT_CONTROL_SET_UNK_04             = 0xE8, /* args: [value]; store in the interaction state */
    ACTOR_SCRIPT_CONTROL_RUN_ACTOR              = 0xE9, /* args: seven bytes; run the actor along its route, hold until done */
    ACTOR_SCRIPT_CONTROL_SET_TINT               = 0xEA, /* args: [r] [g] [b] [steps]; fade or set the actor tint */
    ACTOR_SCRIPT_CONTROL_TOGGLE_HIDDEN          = 0xEB, /* toggle the hidden flag */
    ACTOR_SCRIPT_CONTROL_TOGGLE_NO_SCRIPT_START = 0xEC, /* toggle the no-script-start option */
    ACTOR_SCRIPT_CONTROL_TOGGLE_ROUTE_LOCK      = 0xED, /* toggle the route-lock option */
    ACTOR_SCRIPT_CONTROL_TOGGLE_WAIT_STREAM     = 0xEE, /* toggle the wait-stream option */
    ACTOR_SCRIPT_CONTROL_MARK_MOVING            = 0xEF, /* mark the interaction moving */
} ActorScriptControl;

/* func_801A9944 */
/* Runs one script control opcode. */
MATCH u8 Script_OpsRunControl(void* sub, s32 target, u8 value) {
    u8*    target_bytes;
    u16    next_cursor_e7;
    u16    next_cursor_e8;
    u16    next_cursor_e0e3;
    u16    next_cursor_e2;
    u16    next_cursor;
    Actor* spad_work_ea;
    Actor* spad_work_e5;
    Actor* spad_work_eb;
    Actor* spad_work_ec;
    Actor* spad_work_ed;
    Actor* spad_work_ee;
    Actor* spad_work_e4;
    u8     high_byte;
    u8     state_flags;
    u8     opcode;
    u8     updated_flags;
    u8     low_byte;
    u8     selection;
    u8     result;
    u8*    target_entry_e9;
    u8*    target_entry_ea;
    /* FAKE: keep the E2 command pointer in the retail v1 register. */
    FAKE_REG(u8*, target_entry_e2, "v1");
    ScriptState* state;

    state        = sub;
    target_bytes = (u8*)target;
    opcode       = *(target_bytes + state->cursor);
    selection    = value;
    switch (opcode) {
        case ACTOR_SCRIPT_CONTROL_START_SELECTED:
            state->direction = SELF(Actor)->direction;
            Script_DispatchSelector((target_bytes + state->cursor)[1]);
            state->message_id = (target_bytes + state->cursor)[2];
            func_801A17A0((u8*)state);
            state->flags  = ((state->flags & ~ACTOR_INTERACTION_SCRIPT_REQUEST) | ACTOR_INTERACTION_SCRIPT_PENDING);
            state->cursor = (state->cursor + 2);
            return 0xFFU;
        case ACTOR_SCRIPT_CONTROL_START_FACING_PARTY:
            state->direction = SELF(Actor)->direction;
            state->flags     = (state->flags | ACTOR_INTERACTION_MOVING);
            selection        = g_Game.members[0].facing ^ 0x4;
            Script_DispatchSelector(selection);
            goto block_5; /* E0 and E3 share the operand-read tail */
        case ACTOR_SCRIPT_CONTROL_START_DIRECTION:
            state->direction = (SELF(Actor)->direction & 0x7);
        block_5:
            next_cursor_e0e3  = state->cursor + 1;
            state->cursor     = next_cursor_e0e3;
            state->message_id = *(target_bytes + (next_cursor_e0e3 & HALF_MASK));
            func_801A17A0((u8*)state);
            state_flags   = state->flags;
            updated_flags = state_flags & ~ACTOR_INTERACTION_SCRIPT_REQUEST;
            state->flags  = updated_flags;
            if (SELF(Actor)->option_flags & ACTOR_OPT_NO_SCRIPT_START) {
                state->flags = (state_flags & ~(ACTOR_INTERACTION_SCRIPT_REQUEST | ACTOR_INTERACTION_SCRIPT_PENDING));
            } else {
                state->flags = (updated_flags | ACTOR_INTERACTION_SCRIPT_PENDING);
            }
            goto block_29; /* every command that keeps the selection shares the return */
        case ACTOR_SCRIPT_CONTROL_SET_WAIT:
            target_entry_e2   = target_bytes + state->cursor;
            /* FAKE: retain the second 16-bit load at sub+0xA. */
            next_cursor_e2    = *FAKE_VOLATILE_PTR(u16, &state->cursor);
            high_byte         = target_entry_e2[1];
            low_byte          = target_entry_e2[2];
            next_cursor_e2    = (next_cursor_e2 + 2);
            state->cursor     = next_cursor_e2;
            state->message_id = (low_byte | (high_byte << 8));
            goto block_29; /* every command that keeps the selection shares the return */
        case ACTOR_SCRIPT_CONTROL_CLEAR_ACTOR:
            SELF(Actor)->header.flags = 0;
            goto block_29; /* every command that keeps the selection shares the return */
        case ACTOR_SCRIPT_CONTROL_END_SCRIPT:
            spad_work_e5 = SELF(Actor);
            g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
            spad_work_e5->header.mode = spad_work_e5->unk_03;
            goto block_29; /* every command that keeps the selection shares the return */
        case ACTOR_SCRIPT_CONTROL_SELECT_ROUTE:
            next_cursor_e7 = state->cursor + 1;
            state->cursor  = next_cursor_e7;
            Actor_RunMode(*(target_bytes + (next_cursor_e7 & HALF_MASK)));
            state->steps = 0;
            return 0xFFU;
        case ACTOR_SCRIPT_CONTROL_RUN_ACTOR:
            target_entry_e9 = target_bytes + state->cursor;
            if ((Actor_Run(state, ((s8*)target_entry_e9)[1], ((s8*)target_entry_e9)[2], ((target_entry_e9[3] << 8) | target_entry_e9[4]), (s32)(s16)(target_entry_e9[6] | (target_entry_e9[5] << 8)),
                           (target_bytes + state->cursor)[7], (target_bytes + state->cursor)[8])
                 << 0x18) != 0) {
                state->cursor = (state->cursor - 1);
                result        = 0xFF;
                if (Actor_GetOwner() == 2) {
                    return SELF(Actor)->direction;
                }
                return result;
            }
            next_cursor = state->cursor + 8;
            goto block_28; /* E9 and EA share the cursor store */
        case ACTOR_SCRIPT_CONTROL_TOGGLE_HIDDEN:
            spad_work_eb = SELF(Actor);
            spad_work_eb->header.flags ^= ACTOR_FLAG_HIDDEN;
            goto block_29; /* every command that keeps the selection shares the return */
        case ACTOR_SCRIPT_CONTROL_TOGGLE_NO_SCRIPT_START:
            spad_work_ec               = SELF(Actor);
            spad_work_ec->option_flags = (spad_work_ec->option_flags ^ ACTOR_OPT_NO_SCRIPT_START);
            goto block_29; /* every command that keeps the selection shares the return */
        case ACTOR_SCRIPT_CONTROL_TOGGLE_ROUTE_LOCK:
            spad_work_ed               = SELF(Actor);
            spad_work_ed->option_flags = (spad_work_ed->option_flags ^ ACTOR_OPT_ROUTE_LOCKED);
            goto block_29; /* every command that keeps the selection shares the return */
        case ACTOR_SCRIPT_CONTROL_TOGGLE_WAIT_STREAM:
            spad_work_ee               = SELF(Actor);
            spad_work_ee->option_flags = (spad_work_ee->option_flags ^ ACTOR_OPT_WAIT_STREAM);
            goto block_29; /* every command that keeps the selection shares the return */
        case ACTOR_SCRIPT_CONTROL_SET_UNK_04:
            next_cursor_e8   = state->cursor + 1;
            state->cursor    = next_cursor_e8;
            state->move_mode = *(target_bytes + (next_cursor_e8 & HALF_MASK));
            if (Actor_GetOwner() == 2) {
                selection = 0;
                goto block_29; /* every command that keeps the selection shares the return */
            }
            return selection;
        case ACTOR_SCRIPT_CONTROL_MARK_MOVING:
            state->flags = (state->flags | ACTOR_INTERACTION_MOVING);
            goto block_29; /* every command that keeps the selection shares the return */
        case ACTOR_SCRIPT_CONTROL_RELEASE_ROUTE:
            spad_work_e4               = SELF(Actor);
            SP_REF(u8, 0x3)            = 0xFF;
            spad_work_e4->option_flags = (spad_work_e4->option_flags & ~(ACTOR_OPT_ROUTE_LOCKED | ACTOR_OPT_WAIT_STREAM));
            state->flags               = (state->flags & 0xBF);
            goto block_29; /* every command that keeps the selection shares the return */
        case ACTOR_SCRIPT_CONTROL_SET_TINT:
            spad_work_ea = SELF(Actor);
            if (spad_work_ea->unk_06 != 0xA) {
                target_entry_ea = target_bytes + state->cursor;
                GFX_PaletteAllocFade((u8*)spad_work_ea, target_entry_ea[1], target_entry_ea[2], target_entry_ea[3], target_entry_ea[4]);
            } else {
                spad_work_ea->tint.bytes.rgb.r = (target_bytes + state->cursor)[1];
                SELF(Actor)->tint.bytes.rgb.g  = (target_bytes + state->cursor)[2];
                SELF(Actor)->tint.bytes.rgb.b  = (target_bytes + state->cursor)[3];
            }
            next_cursor = state->cursor + 4;
        block_28:
            state->cursor = next_cursor;
        default:
        block_29:
            result = selection & BYTE_MASK;
            return result;
    }
}
