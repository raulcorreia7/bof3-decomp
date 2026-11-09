#include "area030_04.h"

/* When flag `g_AreaCameraMoving` and flag `D_80144125` are both clear, writes 1 to byte 0x02 and 0 to byte 0x03 of the scratchpad work object. */
MATCH void func_801DAE84(void) {
    if (g_AreaCameraMoving == 0 && D_80144125 == 0) {
        FISHING_STATE->mode_index_02 = 1;
        FISHING_STATE->sub_index_03  = 0;
    }
}
