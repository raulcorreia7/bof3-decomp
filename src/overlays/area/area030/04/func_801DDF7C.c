#include "area030_04.h"

/* Returns 1 and arms the scratchpad work object (byte 0x02 = 8, byte 0x03 = 0) after entering local mode 2 when mask `request` intersects the state halfword `g_InputPressed`. */
MATCH s32 func_801DDF7C(u16 request) {
    if ((g_InputPressed & request) != 0) {
        UI_SetMode(2);
        FISHING_STATE->mode_index_02 = 8;
        FISHING_STATE->sub_index_03  = 0;
        return 1;
    }
    return 0;
}
