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

    record         = TASK(FishingState);
    table          = g_FishingPromptSets;
    column         = record->column;
    row            = table[record->cue_index];
    record->row_4B = row[column];

    panel             = TASK(FishingState);
    value             = D_801E1E7C[panel->row_4B * 3];
    panel->counter_49 = 0;

    state             = TASK(FishingState);
    panel->flags_58   = 0;
    panel->item.raw   = value;
    state->step_timer = 4;

    panel                = TASK(FishingState);
    panel->origin_x      = 0x125;
    panel->handler_index = (panel->handler_index + 1);
}
