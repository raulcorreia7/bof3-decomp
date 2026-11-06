#include "area193_13.h"

MATCH s32 func_801F315C(s32 entry_x, s32 entry_y) {
    if ((entry_x == TO_COORD(1) + COORD_HALF) || (entry_y == TO_COORD(1) + COORD_HALF) || (entry_x == TO_COORD(51) + COORD_HALF) || (entry_y == TO_COORD(51) + COORD_HALF)) {
        Game_SetScriptActive();
        g_SceneEventMode = 0x39;
        g_SceneEventStep = 0xA;
        return 1;
    }
    return 0;
}
