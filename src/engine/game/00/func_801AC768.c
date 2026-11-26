#include "game_00.h"

MATCH void func_801AC768(ScriptState* cursor_state, s32 mode_byte, s32 value_18, s32 value_1C, s32 extra_value) {
    s32    status;
    Actor* slot;

    status = Actor_GetOwner();
    if (status != 1) {
        if (TASK(Actor)->header.mode == ACTOR_MODE_ATTACH) {
            func_801ABEE0();
        }
        TASK(Actor)->header.mode = mode_byte;
        slot                     = TASK(Actor);
        if (slot->header.mode == ACTOR_MODE_ATTACH) {
            slot->unk_18 = value_18 & BYTE_MASK;
            slot->unk_1C = value_1C & BYTE_MASK;
            if (cursor_state->move_mode != 0) {
                func_801AC0A0(extra_value);
            }
            goto advance; /* share the caller step advance */
        }
    } else {
        if (TASK(Actor)->header.step == status) {
            func_801ABEE0();
        }
        if ((mode_byte & BYTE_MASK) == 7) {
            TASK(Actor)->header.step = 1;
            slot                     = TASK(Actor);
            slot->unk_18             = value_18 & BYTE_MASK;
            slot->unk_1C             = value_1C & BYTE_MASK;
            if (cursor_state->move_mode != 0) {
                func_801AC0A0(extra_value);
                cursor_state->steps = 1;
            }
        advance:
            cursor_state->cursor = cursor_state->cursor + 3;
            return;
        }
        ACTOR_CLEAR_STEP();
    }
}
