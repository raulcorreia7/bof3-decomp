#include "engine/slus/slus.h"

/* stages the work record's state byte at +0x29: 4 when byte +0x24 has bit 0x10, 6 when byte 3 of the record
 * pointer at +0x54 has bit 0x20, otherwise g_AreaDrawMode; then runs func_8015A9A4.
 */
MATCH void func_8015A944(void) {
    Actor* work;
    u8     state;

    work = g_Task;
    if ((work->active_flags & 0x10) != 0) {
        state = 4;
    } else if ((work->range_54.table[3] & 0x20) != 0) {
        state = 6;
    } else {
        state = g_AreaDrawMode;
    }

    work->unk_29 = state;
    func_8015A9A4();
}
