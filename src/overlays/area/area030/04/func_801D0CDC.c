#include "area030_04.h"

/* Copies the four AREA030 entry bytes into the scratch record and
 * seeds its panel fields, position limit and state counter. */
MATCH void func_801D0CDC(void) {
    FishingState* panel;
    FishingState* blank;
    FishingState* state;

    TASK(FishingState)->saved_25       = g_Game.members[0].unk_25;
    TASK(FishingState)->saved_26       = g_Game.members[0].unk_26;
    TASK(FishingState)->saved_value_27 = g_Game.members[0].unk_27;
    TASK(FishingState)->saved_value_28 = g_Game.members[0].unk_28;
    TASK(FishingState)->state_29       = 2;
    TASK(FishingState)->active_flags   = 0x80;

    panel                       = TASK(FishingState);
    panel->counter_48           = 0;
    blank                       = TASK(FishingState);
    panel->origin_x             = 0x39;
    panel->origin_y             = 0xC8;
    blank->unk_5C               = 0;
    TASK(FishingState)->tint_5D = 0;
    TASK(FishingState)->tint_5E = 0;
    TASK(FishingState)->tint_5F = 0;

    state                = TASK(FishingState);
    state->cursor_10     = 0xF0;
    state->handler_index = (state->handler_index + 1);
}
