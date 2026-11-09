#include "engine/slus/slus.h"

/* Stages the next two-byte step of the sprite animation stream. */
/* func_8014DB98 */
MATCH void Actor_StageAnimStep(void) {
    u16    index;
    u16    next_index;
    Actor* current_work;
    Actor* first_work;
    u8*    entries;
    u8*    table;
    u8     selected;

    first_work              = g_Task;
    first_work->unk_4A      = *(u8*)(first_work->script + first_work->script_pc);
    current_work            = g_Task;
    index                   = current_work->script_pc;
    entries                 = current_work->script;
    next_index              = index + 1;
    current_work->script_pc = next_index;
    selected                = *(entries + (next_index & HALF_MASK));
    table                   = current_work->range_54.table;
    current_work->script_pc = index + 2;
    current_work->unk_5A    = *(u16*)(table + selected * 2);
}
