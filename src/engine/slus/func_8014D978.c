#include "engine/slus/slus.h"

/* runs down the delay byte at work offset 0x4A; at zero it compares half the staged index (0x58) with the
 * filter byte (0x49): a match zeroes the index and reports 1, otherwise a 0x80 command byte reloads the index from
 * the next byte and reports 1. An expired delay always advances the stream through func_8014DB98.
 */
MATCH u8 func_8014D978(void) {
    Actor* first_work;
    Actor* work;
    u8*    entry;
    u16    index;
    u8     result;

    first_work = g_SpadWork;
    result     = 0;
    if (--first_work->unk_4A == 0) {
        work  = g_SpadWork;
        index = work->script_pc;
        if ((index >> 1) == work->unk_49) {
            work->script_pc = 0;
            result          = 1;
        } else {
            entry = work->source_50 + index;
            if (entry[0] >= 0x80U) {
                work->script_pc = (u16)(entry[1] * 2);
                result          = 1;
            }
        }
        func_8014DB98();
    }
    return result;
}
