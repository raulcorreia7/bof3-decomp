#include "game_00.h"

MATCH void func_801AC768(GameCursorState* cursor_state, s32 mode_byte, s32 value_18, s32 value_1C, s32 extra_value) {
    s32    status;
    Actor* slot;

    status = Actor_GetOwner();
    if (status != 1) {
        if (g_Task->header.mode == 7) {
            func_801ABEE0();
        }
        g_Task->header.mode = mode_byte;
        slot                = g_Task;
        if (slot->header.mode == 7) {
            slot->unk_18 = value_18 & BYTE_MASK;
            slot->unk_1C = value_1C & BYTE_MASK;
            if (cursor_state->unk_04 != 0) {
                func_801AC0A0(extra_value);
            }
            goto advance; /* share the caller step advance */
        }
    } else {
        if (g_Task->header.step == status) {
            func_801ABEE0();
        }
        if ((mode_byte & BYTE_MASK) == 7) {
            g_Task->header.step = 1;
            slot                = g_Task;
            slot->unk_18        = value_18 & BYTE_MASK;
            slot->unk_1C        = value_1C & BYTE_MASK;
            if (cursor_state->unk_04 != 0) {
                func_801AC0A0(extra_value);
                cursor_state->unk_07 = 1;
            }
        advance:
            cursor_state->index_0A = cursor_state->index_0A + 3;
            return;
        }
        ACTOR_CLEAR_STEP();
    }
}
