#include "game_00.h"

MATCH void func_801C5D68(void) {
    s16 value;
    u8* counter;

    counter = &D_80143F51;
    if (*counter != 0) {
        value          = g_ScrollHeight + D_80143F5C;
        g_ScrollHeight = value;
        Area_AdvanceScroll(value);
        (*counter)--;
        return;
    }
    D_80143F4A = 0;
    D_80143FBC &= 0x7F;
}
