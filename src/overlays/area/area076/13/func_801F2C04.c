#include "area076_13.h"

MATCH s32 func_801F2C04(void) {
    s8* state = &g_SceneEventState.mode;

    if (*state == 5) {
        *state                 = 0;
        g_SceneEventState.step = 0;
        D_801448E9             = 0;
    }
    return 0;
}
