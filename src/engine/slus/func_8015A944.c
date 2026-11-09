#include "engine/slus/slus.h"

/* stages the record's state byte at +0x29. */
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

    work->draw_layer = state;
    func_8015A9A4();
}
