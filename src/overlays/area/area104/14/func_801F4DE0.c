#include "area104_14.h"

MATCH void func_801F4DE0(void) {
    u8 count;

    g_Game.current->u.field.mode.unsigned_value = 1;
    count                                       = SELF(Actor)->timer;
    if (count == 0) {
        func_801F4E3C();
    } else {
        SELF(Actor)->timer = count - 1;
        Actor_MovementUpdate();
    }
}
