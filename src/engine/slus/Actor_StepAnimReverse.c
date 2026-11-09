#include "engine/slus/slus.h"

/* Plays the sprite animation backwards. */
/* func_8014DA24 */
MATCH u8 Actor_StepAnimReverse(void) {
    u8  result;
    u8  count;
    u8  selected;
    u16 index;
    u16 prev;

    result         = 0;
    count          = g_Task->unk_4A - 1;
    g_Task->unk_4A = count;
    if ((count & BYTE_MASK) == 0) {
        if (g_Task->script_pc == 0) {
            g_Task->script_pc = g_Task->unk_49 * 2;
            result            = 1;
        }

        index             = g_Task->script_pc;
        prev              = index - 1;
        g_Task->script_pc = prev;
        selected          = *(u8*)(g_Task->script + prev);
        index             = index - 2;
        g_Task->script_pc = index;
        g_Task->unk_4A    = *(u8*)(g_Task->script + index);

        g_Task->unk_5A = *(u16*)(g_Task->range_54.table + selected * 2);
    }
    return result;
}
