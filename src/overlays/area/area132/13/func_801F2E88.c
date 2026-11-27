#include "area132_13.h"

MATCH void func_801F2E88(void) {
    u8* result;
    u8  count;

    if (!(SELF(Actor)->timer & 0x3)) {
        result = func_801F3800();
        if (result != 0) {
            func_801F37A4(result);
        }
    }
    func_801F38B0();
    ACTOR_COUNT_DOWN(SELF(Actor), count, timer);
    if (count == 0) {
        SELF(Actor)->header.step += 1;
    }
}
