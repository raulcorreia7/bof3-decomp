#include "engine/slus/slus.h"

/* copies the staged selection and advances its paired entry index.
 */
MATCH void func_8014DB98(void) {
    u16    index;
    u16    next_index;
    Actor* current_work;
    Actor* first_work;
    u8*    entries;
    u8*    table;
    u8     selected;

    first_work              = g_SpadWork;
    first_work->unk_4A      = (u8) * (u8*)(first_work->source_50 + first_work->script_pc);
    current_work            = g_SpadWork;
    index                   = current_work->script_pc;
    entries                 = current_work->source_50;
    next_index              = index + 1;
    current_work->script_pc = next_index;
    selected                = *(entries + (next_index & HALF_MASK));
    table                   = current_work->range_54.table;
    current_work->script_pc = index + 2;
    current_work->unk_5A    = (u16) * (u16*)(table + selected * 2);
}
