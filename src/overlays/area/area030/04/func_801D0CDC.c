#include "area030_04.h"

/* Copies the four AREA030 entry bytes into the scratch record and
 * seeds its panel fields, position limit and state counter. */
MATCH void func_801D0CDC(void) {
    FishingState* panel;
    FishingState* blank;
    FishingState* state;

    FISHING_STATE->saved_25       = g_BattlePartyBattlers[0].unk_25;
    FISHING_STATE->saved_26       = g_BattlePartyBattlers[0].unk_26;
    FISHING_STATE->saved_value_27 = g_BattlePartyBattlers[0].unk_27;
    FISHING_STATE->saved_value_28 = g_BattlePartyBattlers[0].unk_28;
    FISHING_STATE->state_29       = 2;
    FISHING_STATE->active_flags   = 0x80;

    panel                  = FISHING_STATE;
    panel->counter_48      = 0;
    blank                  = FISHING_STATE;
    panel->origin_x_2E     = 0x39;
    panel->origin_y_30     = 0xC8;
    blank->unk_5C          = 0;
    FISHING_STATE->tint_5D = 0;
    FISHING_STATE->tint_5E = 0;
    FISHING_STATE->tint_5F = 0;

    state                   = FISHING_STATE;
    state->cursor_10        = 0xF0;
    state->handler_index_01 = (state->handler_index_01 + 1);
}
