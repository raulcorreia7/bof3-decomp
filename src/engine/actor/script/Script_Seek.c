#include "engine/slus/slus.h"

/* copies entry byte 1 to work offset 0x49, advances the entry base
 * by 2, then derives the paired-table pointer and processes the next entry.
 */
MATCH void Script_Seek(u16 position) {
    Actor* current_work;
    Actor* first_work;
    u8*    entries;

    first_work                   = SELF(Actor);
    entries                      = first_work->script;
    first_work->unk_49           = entries[1];
    current_work                 = SELF(Actor);
    current_work->script         = current_work->script + 2;
    current_work->script_pc      = position;
    current_work->range_54.table = (u8*)((u16*)current_work->script + current_work->unk_49);
    Script_AnimStageStep();
}
