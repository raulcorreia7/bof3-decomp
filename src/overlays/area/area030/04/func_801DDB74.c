#include "area030_04.h"

/* When flag `g_AreaCameraMoving` is clear, increments counter `D_8014403D` and arms the scratchpad work object. */
MATCH void func_801DDB74(void) {
    u8* counter;

    if (g_AreaCameraMoving == 0) {
        counter = &D_8014403D;
        *counter += 1;
        FISHING_STATE->mode_index_02 = 1;
        FISHING_STATE->sub_index_03  = 0;
    }
}
