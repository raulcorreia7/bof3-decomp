#include "area098_13.h"

MATCH void func_801F3EB0(void) {
    u8* effect;
    s16 timer;

    SELF(Actor)->screen_y = SELF(Actor)->screen_y + 1;
    if ((SELF(Actor)->screen_x & 0x3) == 0) {
        effect = Area_FindFreeWorkRow();
        if (effect != NULL) {
            func_801F4DBC(effect);
        }
    }
    func_801F4E7C();
    timer                 = SELF(Actor)->screen_x - 1;
    SELF(Actor)->screen_x = timer;
    if (timer == 0) {
        SELF(Actor)->timer = 0;
        SELF(Actor)->header.mode++;
    }
}
