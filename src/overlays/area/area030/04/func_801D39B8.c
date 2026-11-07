#include "area030_04.h"

/* Initialises the AREA030 panel scratch record from the current
 * sub-state table entry and advances the panel animation counter. */
MATCH void func_801D39B8(void) {
    FishingState* record;
    FishingState* panel;
    FishingState* state;
    u8(*table)[4];
    u8* row;
    s32 column;
    s32 value;

    record         = FISHING_STATE;
    table          = g_FishingPromptSets;
    column         = record->column_4A;
    row            = table[record->cue_index_06];
    record->row_4B = row[column];

    panel             = FISHING_STATE;
    value             = D_801E1E7C[panel->row_4B * 3];
    panel->counter_49 = 0;

    state                = FISHING_STATE;
    panel->flags_58      = 0;
    panel->item_50.word  = value;
    state->step_timer_09 = 4;

    panel                   = FISHING_STATE;
    panel->origin_x_2E      = 0x125;
    panel->handler_index_01 = (panel->handler_index_01 + 1);
}
