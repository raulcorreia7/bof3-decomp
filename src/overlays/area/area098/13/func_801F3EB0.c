#include "area098_13.h"

MATCH void func_801F3EB0(void) {
    u8* row;
    s16 timer;

    TASK(Actor)->screen_y = TASK(Actor)->screen_y + 1;
    if ((TASK(Actor)->screen_x & 0x3) == 0) {
        row = Area_FindFreeWorkRow();
        if (row != NULL) {
            func_801F4DBC(row);
        }
    }
    func_801F4E7C();
    timer                 = TASK(Actor)->screen_x - 1;
    TASK(Actor)->screen_x = timer;
    if (timer == 0) {
        TASK(Actor)->timer = 0;
        TASK(Actor)->header.mode++;
    }
}
