#include "area076_13.h"

MATCH s32 func_801F2C04(void) {
    s8* state = &g_SaveData.scene_event.mode;

    if (*state == 5) {
        *state                      = 0;
        g_SaveData.scene_event.step = 0;
        D_801448E9                  = 0;
    }
    return 0;
}
