#include "area121_14.h"

MATCH void func_801F5324(void) {
    u8  count;
    u8* work;

    g_Game.current->u.field.mode.unsigned_value = 1;
    work                                        = SELF(u8);
    count                                       = work[0x09];
    if (count == 0) {
        func_801F5380();
    } else {
        work[0x09] = count - 1;
        Actor_MovementUpdate();
    }
}
