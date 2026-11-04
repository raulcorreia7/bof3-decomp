#include "engine/slus/slus.h"

/* copies entry byte 1 to work offset 0x49, advances the entry base
 * by 2, then derives the paired-table pointer and processes the next entry.
 */
/* func_8014D910 */
MATCH void Actor_SeekScript(u16 position) {
    Actor* current_work;
    Actor* first_work;
    u8*    entries;

    first_work                   = g_SpadWork;
    entries                      = first_work->source_50;
    first_work->unk_49           = entries[1];
    current_work                 = g_SpadWork;
    current_work->source_50      = current_work->source_50 + 2;
    current_work->script_pc      = position;
    current_work->range_54.table = (u8*)((u16*)current_work->source_50 + current_work->unk_49);
    func_8014DB98();
}
