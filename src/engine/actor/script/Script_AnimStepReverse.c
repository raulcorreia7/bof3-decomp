#include "engine/slus/slus.h"

/* Plays the sprite animation backwards: counts the step delay (+0x4A) down and, at zero, stages the step before the
 * position (+0x58); at position 0 it wraps to the end and returns 1. Jump steps are ignored.
 */
/* func_8014DA24 */
MATCH u8 Script_AnimStepReverse(void) {
    u8  result;
    u8  count;
    u8  selected;
    u16 index;
    u16 prev;

    result              = 0;
    count               = TASK(Actor)->unk_4A - 1;
    TASK(Actor)->unk_4A = count;
    if ((count & BYTE_MASK) == 0) {
        if (TASK(Actor)->script_pc == 0) {
            TASK(Actor)->script_pc = TASK(Actor)->unk_49 * 2;
            result                 = 1;
        }

        index                  = TASK(Actor)->script_pc;
        prev                   = index - 1;
        TASK(Actor)->script_pc = prev;
        selected               = *(u8*)(TASK(Actor)->script + prev);
        index                  = index - 2;
        TASK(Actor)->script_pc = index;
        TASK(Actor)->unk_4A    = *(u8*)(TASK(Actor)->script + index);

        TASK(Actor)->frame_cells = *(u16*)(TASK(Actor)->range_54.table + selected * 2);
    }
    return result;
}
